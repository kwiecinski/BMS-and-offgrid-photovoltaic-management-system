#include "pozyton_energy_meters.h"
#include "esphome/core/log.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace esphome {
namespace pozyton_energy_meters {

static const char *const TAG = "pozyton";
static constexpr uint8_t SOH = 0x01;
static constexpr uint8_t STX = 0x02;
static constexpr uint8_t ETX = 0x03;
static constexpr uint8_t ACK = 0x06;
static constexpr uint8_t NAK = 0x15;

// Bounded chunks keep the complete dump visible with the default logger buffer.
static void log_debug_frame(const char *direction, const char *label, const uint8_t *data, size_t length) {
  constexpr size_t CHUNK_SIZE = 16;
  for (size_t offset = 0; offset < length; offset += CHUNK_SIZE) {
    std::string hex, text;
    const size_t count = std::min(CHUNK_SIZE, length - offset);
    for (size_t i = 0; i < count; i++) {
      const uint8_t value = data[offset + i];
      char byte[8];
      snprintf(byte, sizeof(byte), "%02X ", value);
      hex += byte;
      switch (value) {
        case '\r': text += "[CR]"; break;
        case '\n': text += "[LF]"; break;
        case SOH: text += "[SOH]"; break;
        case STX: text += "[STX]"; break;
        case ETX: text += "[ETX]"; break;
        case ACK: text += "[ACK]"; break;
        case NAK: text += "[NAK]"; break;
        default:
          if (value >= 0x20 && value <= 0x7E)
            text += static_cast<char>(value);
          else {
            snprintf(byte, sizeof(byte), "[0x%02X]", value);
            text += byte;
          }
      }
    }
    ESP_LOGI(TAG, "%s %s [%u]: HEX=%s ASCII=%s", label, direction, static_cast<unsigned>(offset),
             hex.c_str(), text.c_str());
  }
}

static void log_hex_frame(const char *direction, const char *label, const uint8_t *data, size_t length) {
  constexpr size_t CHUNK_SIZE = 32;
  char hex[CHUNK_SIZE * 3 + 1];
  for (size_t offset = 0; offset < length; offset += CHUNK_SIZE) {
    const size_t count = std::min(CHUNK_SIZE, length - offset);
    size_t used = 0;
    for (size_t i = 0; i < count; i++)
      used += snprintf(hex + used, sizeof(hex) - used, "%02X%s", data[offset + i], i + 1 == count ? "" : " ");
    ESP_LOGV(TAG, "%s %s frame[%u..%u]: %s", label, direction, static_cast<unsigned>(offset),
             static_cast<unsigned>(offset + count - 1), hex);
  }
}

void PozytonBus::add_meter(MeterModel model, const std::string &name, const std::string &address,
                           uint32_t update_interval_ms) {
  Meter meter;
  meter.model = model;
  meter.name = name;
  meter.address = address;
  meter.update_interval_ms = update_interval_ms;
  meter.next_poll_ms = 0;
  this->meters_.push_back(meter);
}

void PozytonBus::set_sensor(uint8_t meter_index, Measurement measurement, sensor::Sensor *entity) {
  if (meter_index >= this->meters_.size() || measurement >= MEASUREMENT_COUNT || entity == nullptr) {
    ESP_LOGE(TAG, "Ignoring invalid sensor registration (meter=%u, measurement=%u)", meter_index,
             static_cast<unsigned>(measurement));
    return;
  }
  this->meters_[meter_index].sensors[measurement] = entity;
}

void PozytonBus::set_connection_sensor(uint8_t meter_index, binary_sensor::BinarySensor *entity) {
  if (meter_index < this->meters_.size())
    this->meters_[meter_index].connection_sensor = entity;
}

void PozytonBus::set_last_success_sensor(uint8_t meter_index, text_sensor::TextSensor *entity) {
  if (meter_index < this->meters_.size())
    this->meters_[meter_index].last_success_sensor = entity;
}

void PozytonBus::set_error_counter_sensor(uint8_t meter_index, sensor::Sensor *entity) {
  if (meter_index < this->meters_.size())
    this->meters_[meter_index].error_counter_sensor = entity;
}

void PozytonBus::setup() {
  if (this->direction_pin_ != nullptr) {
    this->direction_pin_->setup();
    this->direction_pin_->digital_write(false);
  }
  this->next_log_ms_ = millis() + 10000;
  ESP_LOGI(TAG, "Shared Pozyton bus ready at %u baud; %u meter(s) configured", static_cast<unsigned>(this->baud_rate_),
           static_cast<unsigned>(this->meters_.size()));
}

void PozytonBus::dump_config() {
  ESP_LOGCONFIG(TAG, "Pozyton shared RS485 bus:");
  ESP_LOGCONFIG(TAG, "  Baud rate: %u", static_cast<unsigned>(this->baud_rate_));
  ESP_LOGCONFIG(TAG, "  Response timeout: %u ms", static_cast<unsigned>(this->response_timeout_ms_));
  ESP_LOGCONFIG(TAG, "  First response debug: %s", this->debug_first_response_ ? "ON" : "OFF");
  for (const auto &meter : this->meters_) {
    ESP_LOGCONFIG(TAG, "  %s '%s', address '%s', poll interval %u ms", model_name_(meter.model),
                  meter.name.c_str(), meter.address.c_str(), static_cast<unsigned>(meter.update_interval_ms));
  }
}

void PozytonBus::loop() {
  const uint32_t now = millis();
  if (this->state_ == State::TX_DRAIN) {
    if (static_cast<int32_t>(now - this->tx_done_at_) >= 0)
      this->handle_tx_drain_();
  } else if (this->state_ == State::WAIT_RESPONSE) {
    this->read_uart_();
    if (this->state_ == State::WAIT_RESPONSE && static_cast<int32_t>(now - this->response_deadline_) >= 0)
      this->handle_timeout_();
  }

  if (this->state_ == State::IDLE && !this->has_active_meter_)
    this->start_next_meter_();

  if (static_cast<int32_t>(now - this->next_log_ms_) >= 0) {
    this->next_log_ms_ = now + 10000;
    for (const auto &meter : this->meters_) {
      ESP_LOGI(TAG, "%s '%s' (%s) latest readings:", model_name_(meter.model), meter.name.c_str(),
               meter.address.c_str());
      bool logged = false;
      for (size_t i = 0; i < meter.sensors.size(); i++) {
        const auto *entity = meter.sensors[i];
        if (entity == nullptr)
          continue;
        logged = true;
        if (entity->has_state())
          ESP_LOGI(TAG, "  measurement[%u] = %.6f", static_cast<unsigned>(i), entity->get_state());
        else
          ESP_LOGI(TAG, "  measurement[%u] = not available", static_cast<unsigned>(i));
      }
      if (!logged)
        ESP_LOGI(TAG, "  no measurement entities configured");
    }
  }
}

void PozytonBus::start_next_meter_() {
  if (this->meters_.empty())
    return;
  const uint32_t now = millis();
  for (size_t offset = 0; offset < this->meters_.size(); offset++) {
    const uint8_t index = (this->active_meter_index_ + offset) % this->meters_.size();
    Meter &meter = this->meters_[index];
    if (static_cast<int32_t>(now - meter.next_poll_ms) < 0)
      continue;
    this->active_meter_index_ = index;
    this->has_active_meter_ = true;
    this->build_request_list_();
    if (meter.request_count == 0) {
      meter.next_poll_ms = now + meter.update_interval_ms;
      this->has_active_meter_ = false;
      return;
    }
    meter.reading_succeeded = false;
    meter.request_index = 0;
    meter.retry_count = 0;
    this->start_session_();
    return;
  }
}

void PozytonBus::build_request_list_() {
  Meter &meter = this->meters_[this->active_meter_index_];
  meter.request_count = 0;
  auto add = [&meter](Request request) {
    if (meter.request_count < MAX_REQUESTS)
      meter.requests[meter.request_count++] = request;
  };
  if (meter.sensors[MEASUREMENT_ACTIVE_ENERGY_IMPORT] != nullptr) add(Request::ENERGY_PP);
  if (meter.sensors[MEASUREMENT_ACTIVE_ENERGY_EXPORT] != nullptr) add(Request::ENERGY_PM);
  if (meter.sensors[MEASUREMENT_REACTIVE_ENERGY_POSITIVE] != nullptr) add(Request::ENERGY_QP);
  if (meter.sensors[MEASUREMENT_REACTIVE_ENERGY_NEGATIVE] != nullptr) add(Request::ENERGY_QM);
  if (meter.sensors[MEASUREMENT_FREQUENCY] != nullptr) add(Request::FREQUENCY);
  if (has_any_sensor_(meter, {MEASUREMENT_ACTIVE_POWER_L1, MEASUREMENT_ACTIVE_POWER_L2,
                              MEASUREMENT_ACTIVE_POWER_L3, MEASUREMENT_ACTIVE_POWER_TOTAL}))
    add(Request::ACTIVE_POWER);
  if (has_any_sensor_(meter, {MEASUREMENT_REACTIVE_POWER_L1, MEASUREMENT_REACTIVE_POWER_L2,
                              MEASUREMENT_REACTIVE_POWER_L3, MEASUREMENT_REACTIVE_POWER_TOTAL}))
    add(Request::REACTIVE_POWER);
  if (has_any_sensor_(meter, {MEASUREMENT_VOLTAGE_L1, MEASUREMENT_VOLTAGE_L2, MEASUREMENT_VOLTAGE_L3}))
    add(Request::VOLTAGE);
  if (has_any_sensor_(meter, {MEASUREMENT_CURRENT_L1, MEASUREMENT_CURRENT_L2, MEASUREMENT_CURRENT_L3}))
    add(Request::CURRENT);
  if (meter.model == METER_EABM && meter.sensors[MEASUREMENT_NEUTRAL_TANGENT] != nullptr)
    add(Request::TANGENT);
}

void PozytonBus::start_session_() {
  Meter &meter = this->meters_[this->active_meter_index_];
  size_t discarded = 0;
  while (this->available() && discarded < this->rx_buffer_.size()) {
    uint8_t ignored;
    this->read_byte(&ignored);
    discarded++;
  }
  if (discarded == this->rx_buffer_.size()) {
    this->record_error_(meter, "pre-session UART drain", "stale receive buffer exceeded drain limit");
    this->finish_meter_(false);
    return;
  }
  this->rx_length_ = 0;
  if (meter.model == METER_EABM) {
    this->send_text_("/?" + meter.address + "!\r\n", Expect::IDENTIFICATION, "EABM identification");
  } else {
    this->send_text_("/A" + meter.address + "\r\n", Expect::ADDRESS, "SEAB address handshake");
  }
}

void PozytonBus::start_next_request_() {
  Meter &meter = this->meters_[this->active_meter_index_];
  if (meter.request_index >= meter.request_count) {
    this->send_binary_(std::string(1, SOH) + "B0" + static_cast<char>(ETX), Expect::EXIT_ACK,
                       "register mode exit", true);
    return;
  }

  this->active_request_ = meter.requests[meter.request_index];
  std::string code;
  switch (this->active_request_) {
    case Request::ENERGY_PP: code = "EPP0()"; break;
    case Request::ENERGY_PM: code = "EPM0()"; break;
    case Request::ENERGY_QP: code = "EQP0()"; break;
    case Request::ENERGY_QM: code = "EQM0()"; break;
    case Request::FREQUENCY: code = "F()"; break;
    case Request::ACTIVE_POWER: code = "P()"; break;
    case Request::REACTIVE_POWER: code = "Q()"; break;
    case Request::VOLTAGE: code = "U()"; break;
    case Request::CURRENT: code = "I()"; break;
    case Request::TANGENT: code = "TF()"; break;
  }
  const std::string body = std::string(1, SOH) + "R1" + static_cast<char>(STX) + code + static_cast<char>(ETX);
  this->send_binary_(body, Expect::MEASUREMENT, request_name_(this->active_request_), true);
}

void PozytonBus::send_text_(const std::string &frame, Expect expect, const char *stage) {
  this->expect_ = expect;
  this->active_stage_ = stage;
  this->last_tx_frame_ = frame;
  this->send_buffer_();
}

void PozytonBus::send_binary_(std::string frame, Expect expect, const char *stage, bool add_bcc) {
  if (add_bcc) {
    uint8_t bcc = 0;
    const size_t begin = frame.find(static_cast<char>(SOH)) != std::string::npos
                             ? frame.find(static_cast<char>(SOH)) + 1
                             : frame.find(static_cast<char>(STX)) + 1;
    for (size_t i = begin; i < frame.size(); i++)
      bcc ^= static_cast<uint8_t>(frame[i]);
    frame.push_back(static_cast<char>(bcc));
  }
  this->expect_ = expect;
  this->active_stage_ = stage;
  this->last_tx_frame_ = frame;
  this->send_buffer_();
}

void PozytonBus::send_buffer_() {
  if (this->last_tx_frame_.empty() || this->last_tx_frame_.size() > this->tx_buffer_.size()) {
    this->fail_meter_("outgoing frame length invalid");
    return;
  }
  this->rx_length_ = 0;
  this->debug_rx_length_ = 0;
  for (size_t i = 0; i < this->last_tx_frame_.size(); i++)
    this->tx_buffer_[i] = static_cast<uint8_t>(this->last_tx_frame_[i]);
  this->tx_length_ = this->last_tx_frame_.size();
  if (this->direction_pin_ != nullptr)
    this->direction_pin_->digital_write(true);
  this->write_array(this->tx_buffer_.data(), this->tx_length_);
  // 7E1 = one start + seven data + one parity + one stop = ten bits.
  const uint32_t wire_time_ms = (this->tx_length_ * 10000U + this->baud_rate_ - 1U) / this->baud_rate_;
  this->tx_done_at_ = millis() + wire_time_ms + 3U;
  this->state_ = State::TX_DRAIN;
}

void PozytonBus::handle_tx_drain_() {
  if (this->direction_pin_ != nullptr)
    this->direction_pin_->digital_write(false);
  this->state_ = State::WAIT_RESPONSE;
  uint32_t timeout = this->response_timeout_ms_;
  if (this->expect_ == Expect::MODE_REQUEST &&
      this->meters_[this->active_meter_index_].model == METER_SEAB)
    timeout = std::max<uint32_t>(timeout, 1300U);
  this->response_deadline_ = millis() + timeout;
  // Log only after switching back to RX, so logging does not hold DIR high.
  log_hex_frame("TX", current_meter_label_().c_str(), this->tx_buffer_.data(), this->tx_length_);
  ESP_LOGV(TAG, "%s %s: TX %u byte(s)", current_meter_label_().c_str(), this->active_stage_.c_str(),
           static_cast<unsigned>(this->tx_length_));
  if (this->capturing_first_response_()) {
    ESP_LOGI(TAG, "%s FIRST TX: %s, %u baud 7E1, %u byte(s); DIR=RX, timeout=%u ms",
             current_meter_label_().c_str(), this->active_stage_.c_str(), static_cast<unsigned>(this->baud_rate_),
             static_cast<unsigned>(this->tx_length_), static_cast<unsigned>(timeout));
    log_debug_frame("FIRST TX", this->meters_[this->active_meter_index_].name.c_str(),
                    this->tx_buffer_.data(), this->tx_length_);
  }
}

bool PozytonBus::capturing_first_response_() const {
  return this->debug_first_response_ && this->has_active_meter_ &&
         !this->meters_[this->active_meter_index_].first_response_logged;
}

void PozytonBus::log_first_response_(const char *result) {
  if (!this->capturing_first_response_())
    return;
  Meter &meter = this->meters_[this->active_meter_index_];
  ESP_LOGI(TAG, "%s FIRST RX: %s, stage=%s, %u raw byte(s)", current_meter_label_().c_str(), result,
           this->active_stage_.c_str(), static_cast<unsigned>(this->debug_rx_length_));
  log_debug_frame("FIRST RX", meter.name.c_str(), this->debug_rx_buffer_.data(), this->debug_rx_length_);
  // A timeout with no bytes must not consume the first actual reply dump.
  if (this->debug_rx_length_ != 0)
    meter.first_response_logged = true;
}

void PozytonBus::read_uart_() {
  uint8_t value;
  while (this->available()) {
    if (!this->read_byte(&value))
      break;
    // Capture before filtering NULs or validating framing/BCC.
    if (this->capturing_first_response_() && this->debug_rx_length_ < this->debug_rx_buffer_.size())
      this->debug_rx_buffer_[this->debug_rx_length_++] = value;
    if (this->rx_length_ == 0 && value == 0x00)
      continue;
    if (this->rx_length_ >= this->rx_buffer_.size()) {
      this->log_first_response_("receive buffer overflow; dump limited to 512 bytes");
      this->record_error_(this->meters_[this->active_meter_index_], this->active_stage_.c_str(), "receive buffer overflow");
      this->retry_or_fail_("receive buffer overflow");
      return;
    }
    this->rx_buffer_[this->rx_length_++] = value;
    if (this->is_frame_complete_()) {
      this->handle_response_();
      return;
    }
  }
}

bool PozytonBus::is_frame_complete_() const {
  if (this->rx_length_ == 0)
    return false;
  if (this->rx_buffer_[0] == ACK || this->rx_buffer_[0] == NAK)
    return true;
  if (this->rx_buffer_[0] == '/')
    return this->rx_buffer_[this->rx_length_ - 1] == '\n';
  if (this->rx_length_ >= 2 && this->rx_buffer_[this->rx_length_ - 2] == ETX)
    return true;
  return false;
}

bool PozytonBus::validate_bcc_(const std::string &frame) const {
  if (frame.size() < 3 || static_cast<uint8_t>(frame[frame.size() - 2]) != ETX)
    return false;
  size_t start = frame.find(static_cast<char>(SOH));
  if (start != std::string::npos)
    start++;
  else {
    start = frame.find(static_cast<char>(STX));
    if (start == std::string::npos)
      return false;
    start++;
  }
  uint8_t bcc = 0;
  for (size_t i = start; i < frame.size() - 1; i++)
    bcc ^= static_cast<uint8_t>(frame[i]);
  return bcc == static_cast<uint8_t>(frame.back());
}

void PozytonBus::handle_response_() {
  this->log_first_response_("frame complete, before validation");
  std::string response(this->rx_buffer_.begin(), this->rx_buffer_.begin() + this->rx_length_);
  this->rx_length_ = 0;
  Meter &meter = this->meters_[this->active_meter_index_];
  ESP_LOGV(TAG, "%s %s: RX %u byte(s)", current_meter_label_().c_str(), this->active_stage_.c_str(),
           static_cast<unsigned>(response.size()));
  log_hex_frame("RX", current_meter_label_().c_str(), reinterpret_cast<const uint8_t *>(response.data()),
                response.size());

  const bool is_ack = response.size() == 1 && static_cast<uint8_t>(response[0]) == ACK;
  const bool is_nak = response.size() == 1 && static_cast<uint8_t>(response[0]) == NAK;
  if (is_nak) {
    this->retry_or_fail_("meter returned NAK");
    return;
  }
  if ((this->expect_ == Expect::AUTH_ACK || this->expect_ == Expect::EXIT_ACK) && !is_ack) {
    this->retry_or_fail_("expected ACK");
    return;
  }
  if (this->expect_ == Expect::ADDRESS) {
    const std::string expected = "/g" + meter.address + "\r\n";
    if (response != expected) {
      this->retry_or_fail_("address handshake response did not match configured meter address");
      return;
    }
    meter.retry_count = 0;
    this->send_text_("/?!\r\n", Expect::IDENTIFICATION, "SEAB identification");
    return;
  }
  if (this->expect_ == Expect::IDENTIFICATION) {
    const bool model_ok = response.find(meter.model == METER_EABM ? "EABM" : "sEA") != std::string::npos;
    if (!model_ok) {
      this->retry_or_fail_("unexpected identification response");
      return;
    }
    meter.retry_count = 0;
    // B/b in the manuals is a speed placeholder, not a literal 'B'.
    // Both RS485 interfaces ignore this speed selector and retain their fixed baud rate.
    const std::string mode = std::string(1, ACK) + "041\r\n";
    this->send_text_(mode, Expect::MODE_REQUEST, "register mode selection");
    return;
  }
  if (this->expect_ == Expect::MODE_REQUEST) {
    if (response.size() < 5 || response[0] != static_cast<char>(SOH) || response.find("P0") == std::string::npos ||
        !this->validate_bcc_(response)) {
      this->retry_or_fail_("invalid authorization request (P0)");
      return;
    }
    meter.retry_count = 0;
    const std::string auth = this->make_binary_frame_(std::string(1, SOH) + "P1" + static_cast<char>(STX) + "()" +
                                                       static_cast<char>(ETX));
    this->send_binary_(auth, Expect::AUTH_ACK, "read-only authorization response", false);
    return;
  }
  if (this->expect_ == Expect::AUTH_ACK) {
    if (!is_ack) {
      this->retry_or_fail_("meter rejected read-only authorization");
      return;
    }
    meter.retry_count = 0;
    this->start_next_request_();
    return;
  }
  if (this->expect_ == Expect::MEASUREMENT) {
    if (!this->validate_bcc_(response)) {
      this->retry_or_fail_("invalid BCC on register response");
      return;
    }
    const std::string payload = response.substr(1, response.size() - 3);
    if (!this->process_measurement_(meter, this->active_request_, payload)) {
      this->retry_or_fail_("invalid measurement format or response identifier");
      return;
    }
    meter.retry_count = 0;
    meter.reading_succeeded = true;
    meter.request_index++;
    this->start_next_request_();
    return;
  }
  if (this->expect_ == Expect::EXIT_ACK) {
    this->finish_meter_(meter.reading_succeeded);
  }
}

void PozytonBus::handle_timeout_() {
  this->log_first_response_(this->debug_rx_length_ == 0 ? "timeout, no bytes received" : "timeout, incomplete/filtered response");
  this->retry_or_fail_("response timeout");
}

void PozytonBus::retry_or_fail_(const char *reason) {
  Meter &meter = this->meters_[this->active_meter_index_];
  if (meter.retry_count < 1) {
    meter.retry_count++;
    meter.error_count++;
    this->update_error_counter_(meter);
    ESP_LOGW(TAG, "%s %s: %s; retry %u/1", current_meter_label_().c_str(), this->active_stage_.c_str(), reason,
             meter.retry_count);
    this->send_buffer_();
    return;
  }
  if (this->expect_ == Expect::MEASUREMENT) {
    this->fail_request_(reason);
    return;
  }
  this->fail_meter_(reason);
}

void PozytonBus::fail_request_(const char *reason) {
  Meter &meter = this->meters_[this->active_meter_index_];
  this->record_error_(meter, request_name_(this->active_request_), reason);
  meter.request_index++;
  meter.retry_count = 0;
  this->start_next_request_();
}

void PozytonBus::fail_meter_(const char *reason) {
  Meter &meter = this->meters_[this->active_meter_index_];
  this->record_error_(meter, this->active_stage_.c_str(), reason);
  this->finish_meter_(meter.reading_succeeded);
}

void PozytonBus::finish_meter_(bool successful) {
  Meter &meter = this->meters_[this->active_meter_index_];
  this->set_online_(meter, successful);
  meter.next_poll_ms = millis() + meter.update_interval_ms;
  this->active_meter_index_ = (this->active_meter_index_ + 1) % this->meters_.size();
  this->has_active_meter_ = false;
  this->state_ = State::IDLE;
  this->rx_length_ = 0;
  if (this->direction_pin_ != nullptr)
    this->direction_pin_->digital_write(false);
  if (successful && meter.last_success_sensor != nullptr) {
    char uptime[32];
    snprintf(uptime, sizeof(uptime), "uptime +%lu s", static_cast<unsigned long>(millis() / 1000UL));
    meter.last_success_sensor->publish_state(uptime);
  }
  if (successful) {
    ESP_LOGD(TAG, "%s: poll cycle completed", current_meter_label_().c_str());
  }
}

void PozytonBus::set_online_(Meter &meter, bool online) {
  meter.online = online;
  if (meter.connection_sensor != nullptr)
    meter.connection_sensor->publish_state(online);
}

void PozytonBus::record_error_(Meter &meter, const char *stage, const char *reason) {
  meter.error_count++;
  meter.last_error = reason;
  this->update_error_counter_(meter);
  set_online_(meter, false);
  ESP_LOGW(TAG, "%s %s failed: %s", current_meter_label_().c_str(), stage, reason);
}

void PozytonBus::update_error_counter_(Meter &meter) {
  if (meter.error_counter_sensor != nullptr)
    meter.error_counter_sensor->publish_state(static_cast<float>(meter.error_count));
}

bool PozytonBus::process_measurement_(Meter &meter, Request request, const std::string &payload) {
  auto publish_if_configured = [this, &meter](Measurement key, float value) {
    if (meter.sensors[key] != nullptr)
      this->publish_(meter, key, value);
  };
  auto get_record = [&payload](const std::string &wanted, float *value, float *scale) -> bool {
    size_t line_start = 0;
    while (line_start < payload.size()) {
      size_t line_end = payload.find('\n', line_start);
      if (line_end == std::string::npos)
        line_end = payload.size();
      std::string line = payload.substr(line_start, line_end - line_start);
      line_start = line_end + 1;
      while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
      const size_t open = line.find('(');
      if (open == std::string::npos)
        continue;
      std::string id = line.substr(0, open);
      while (!id.empty() && id.back() == '.') id.pop_back();
      std::string field = line.substr(open + 1, line.find(')', open) == std::string::npos
                                                   ? std::string::npos
                                                   : line.find(')', open) - open - 1);
      const size_t unit = field.find('*');
      *scale = 1.0f;
      if (unit != std::string::npos) {
        const std::string unit_text = field.substr(unit + 1);
        if (unit_text.find("kW") != std::string::npos || unit_text.find("kvar") != std::string::npos)
          *scale = 1000.0f;
        field.resize(unit);
      }
      if (id == wanted && parse_number_(field, value))
        return true;
    }
    return false;
  };
  auto parse_grouped = [&payload](const std::string &id, std::vector<float> *values, float scale,
                                  size_t value_limit = SIZE_MAX) -> bool {
    const size_t marker = payload.find(id + "(");
    if (marker == std::string::npos)
      return false;
    const size_t open = payload.find('(', marker);
    const size_t close = payload.find(')', open);
    if (close == std::string::npos)
      return false;
    std::string fields = payload.substr(open + 1, close - open - 1);
    size_t start = 0;
    while (start <= fields.size()) {
      size_t end = fields.find(';', start);
      if (end == std::string::npos) end = fields.size();
      const std::string field = fields.substr(start, end - start);
      float value;
      if (!parse_number_(field, &value))
        return false;
      values->push_back(value * scale);
      if (values->size() >= value_limit)
        return true;
      if (end == fields.size()) break;
      start = end + 1;
    }
    return true;
  };

  float value = 0.0f;
  float scale = 1.0f;
  switch (request) {
    case Request::ENERGY_PP:
    case Request::ENERGY_PM:
    case Request::ENERGY_QP:
    case Request::ENERGY_QM: {
      const char *wanted = request == Request::ENERGY_PP ? "0.8.0" : request == Request::ENERGY_PM ? "1.8.0" :
                           request == Request::ENERGY_QP ? "2.8.0" : "3.8.0";
      if (!get_record(wanted, &value, &scale)) return false;
      const Measurement key = request == Request::ENERGY_PP ? MEASUREMENT_ACTIVE_ENERGY_IMPORT :
                              request == Request::ENERGY_PM ? MEASUREMENT_ACTIVE_ENERGY_EXPORT :
                              request == Request::ENERGY_QP ? MEASUREMENT_REACTIVE_ENERGY_POSITIVE :
                                                               MEASUREMENT_REACTIVE_ENERGY_NEGATIVE;
      publish_if_configured(key, value);
      return true;
    }
    case Request::FREQUENCY: {
      const char *wanted = meter.model == METER_EABM ? "14.7.0" : "97.6.0";
      if (!get_record(wanted, &value, &scale)) return false;
      publish_if_configured(MEASUREMENT_FREQUENCY, value);
      return true;
    }
    case Request::TANGENT:
      if (!get_record("103.3", &value, &scale)) return false;
      publish_if_configured(MEASUREMENT_NEUTRAL_TANGENT, value);
      return true;
    case Request::ACTIVE_POWER:
    case Request::REACTIVE_POWER: {
      const bool active = request == Request::ACTIVE_POWER;
      std::array<float, 4> values{};
      std::array<bool, 4> found{};
      if (meter.model == METER_SEAB) {
        std::vector<float> parsed;
        const bool has_fraction = payload.find('.') != std::string::npos;
        const float unit_scale = has_fraction ? 1000.0f : 1.0f;
        if (!parse_grouped(active ? "107" : "109", &parsed, unit_scale) || parsed.size() < 4)
          return false;
        for (size_t i = 0; i < 4; i++) values[i] = parsed[i];
      } else {
        const std::array<std::array<const char *, 2>, 4> active_ids{{
            {{"21.7.0", "22.7.0"}}, {{"41.7.0", "42.7.0"}}, {{"61.7.0", "62.7.0"}}, {{"1.7.0", "2.7.0"}}}};
        const std::array<std::array<const char *, 2>, 4> reactive_ids{{
            {{"23.7.0", "24.7.0"}}, {{"43.7.0", "44.7.0"}}, {{"63.7.0", "64.7.0"}}, {{"3.7.0", "4.7.0"}}}};
        const auto &ids = active ? active_ids : reactive_ids;
        for (size_t i = 0; i < ids.size(); i++) {
          for (size_t j = 0; j < ids[i].size(); j++) {
            if (get_record(ids[i][j], &value, &scale)) {
              values[i] += value * scale;
              found[i] = true;
            }
          }
        }
        if (std::find(found.begin(), found.end(), true) == found.end()) return false;
      }
      const Measurement base = active ? MEASUREMENT_ACTIVE_POWER_L1 : MEASUREMENT_REACTIVE_POWER_L1;
      for (size_t i = 0; i < 3; i++) publish_if_configured(static_cast<Measurement>(base + i), values[i]);
      publish_if_configured(active ? MEASUREMENT_ACTIVE_POWER_TOTAL : MEASUREMENT_REACTIVE_POWER_TOTAL, values[3]);
      return true;
    }
    case Request::VOLTAGE:
    case Request::CURRENT: {
      const bool voltage = request == Request::VOLTAGE;
      std::array<float, 3> values{};
      if (meter.model == METER_SEAB) {
        std::vector<float> parsed;
        if (!parse_grouped(voltage ? "97.5.6" : "97.4.4", &parsed, 1.0f, 3) || parsed.size() < 3)
          return false;
        for (size_t i = 0; i < 3; i++) values[i] = parsed[i];
      } else {
        const std::array<const char *, 3> voltage_ids{{"32.7.0", "52.7.0", "72.7.0"}};
        const std::array<const char *, 3> current_ids{{"31.7.0", "51.7.0", "71.7.0"}};
        const auto &ids = voltage ? voltage_ids : current_ids;
        for (size_t i = 0; i < ids.size(); i++) {
          if (!get_record(ids[i], &values[i], &scale)) return false;
          values[i] *= scale;
        }
      }
      const Measurement base = voltage ? MEASUREMENT_VOLTAGE_L1 : MEASUREMENT_CURRENT_L1;
      for (size_t i = 0; i < 3; i++) publish_if_configured(static_cast<Measurement>(base + i), values[i]);
      return true;
    }
  }
  return false;
}

void PozytonBus::publish_(Meter &meter, Measurement measurement, float value) {
  sensor::Sensor *entity = meter.sensors[measurement];
  if (entity != nullptr && std::isfinite(value))
    entity->publish_state(value);
}

bool PozytonBus::has_any_sensor_(const Meter &meter, std::initializer_list<Measurement> measurements) const {
  for (Measurement measurement : measurements) {
    if (meter.sensors[measurement] != nullptr)
      return true;
  }
  return false;
}

std::string PozytonBus::make_binary_frame_(const std::string &body) const {
  uint8_t bcc = 0;
  for (size_t i = 1; i < body.size(); i++)
    bcc ^= static_cast<uint8_t>(body[i]);
  return body + static_cast<char>(bcc);
}

bool PozytonBus::parse_number_(const std::string &text, float *value) {
  if (value == nullptr || text.empty()) return false;
  const char *begin = text.c_str();
  while (*begin == ' ' || *begin == '\t') begin++;
  if (*begin == '\0') return false;
  char *end = nullptr;
  const float parsed = strtof(begin, &end);
  if (end == begin || !std::isfinite(parsed)) return false;
  while (*end == ' ' || *end == '\t') end++;
  if (*end != '\0') return false;
  *value = parsed;
  return true;
}

std::string PozytonBus::current_meter_label_() const {
  if (!this->has_active_meter_ || this->active_meter_index_ >= this->meters_.size()) return "bus";
  const Meter &meter = this->meters_[this->active_meter_index_];
  return std::string(model_name_(meter.model)) + " '" + meter.name + "' (" + meter.address + ")";
}

const char *PozytonBus::model_name_(MeterModel model) { return model == METER_EABM ? "EABM" : "SEAB"; }

const char *PozytonBus::request_name_(Request request) {
  switch (request) {
    case Request::ENERGY_PP: return "EPP0";
    case Request::ENERGY_PM: return "EPM0";
    case Request::ENERGY_QP: return "EQP0";
    case Request::ENERGY_QM: return "EQM0";
    case Request::FREQUENCY: return "F";
    case Request::ACTIVE_POWER: return "P";
    case Request::REACTIVE_POWER: return "Q";
    case Request::VOLTAGE: return "U";
    case Request::CURRENT: return "I";
    case Request::TANGENT: return "TF";
  }
  return "unknown";
}

}  // namespace pozyton_energy_meters
}  // namespace esphome
