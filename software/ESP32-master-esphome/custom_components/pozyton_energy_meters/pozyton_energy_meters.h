#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include <array>
#include <initializer_list>
#include <string>
#include <vector>

namespace esphome {
namespace pozyton_energy_meters {

enum MeterModel : uint8_t { METER_SEAB, METER_EABM };

enum Measurement : uint8_t {
  MEASUREMENT_VOLTAGE_L1,
  MEASUREMENT_VOLTAGE_L2,
  MEASUREMENT_VOLTAGE_L3,
  MEASUREMENT_CURRENT_L1,
  MEASUREMENT_CURRENT_L2,
  MEASUREMENT_CURRENT_L3,
  MEASUREMENT_ACTIVE_POWER_L1,
  MEASUREMENT_ACTIVE_POWER_L2,
  MEASUREMENT_ACTIVE_POWER_L3,
  MEASUREMENT_ACTIVE_POWER_TOTAL,
  MEASUREMENT_REACTIVE_POWER_L1,
  MEASUREMENT_REACTIVE_POWER_L2,
  MEASUREMENT_REACTIVE_POWER_L3,
  MEASUREMENT_REACTIVE_POWER_TOTAL,
  MEASUREMENT_ACTIVE_ENERGY_IMPORT,
  MEASUREMENT_ACTIVE_ENERGY_EXPORT,
  MEASUREMENT_REACTIVE_ENERGY_POSITIVE,
  MEASUREMENT_REACTIVE_ENERGY_NEGATIVE,
  MEASUREMENT_FREQUENCY,
  MEASUREMENT_COUNT
};

class PozytonBus : public Component, public uart::UARTDevice {
 public:
  void set_direction_pin(InternalGPIOPin *pin) { this->direction_pin_ = pin; }
  void set_baud_rate(uint32_t baud_rate) { this->baud_rate_ = baud_rate; }
  void set_response_timeout(uint32_t timeout_ms) { this->response_timeout_ms_ = timeout_ms; }
  void set_debug_first_response(bool enabled) { this->debug_first_response_ = enabled; }
  void add_meter(MeterModel model, const std::string &name, const std::string &address, uint32_t update_interval_ms);
  void set_sensor(uint8_t meter_index, Measurement measurement, sensor::Sensor *entity);
  void set_connection_sensor(uint8_t meter_index, binary_sensor::BinarySensor *entity);
  void set_last_success_sensor(uint8_t meter_index, text_sensor::TextSensor *entity);
  void set_error_counter_sensor(uint8_t meter_index, sensor::Sensor *entity);

  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  static constexpr size_t RX_BUFFER_SIZE = 512;
  static constexpr size_t MAX_REQUESTS = 9;

  enum class State : uint8_t { IDLE, TX_DRAIN, WAIT_RESPONSE };
  enum class Expect : uint8_t { ADDRESS, IDENTIFICATION, MODE_REQUEST, AUTH_ACK, MEASUREMENT, EXIT_ACK };
  enum class Request : uint8_t { ENERGY_PP, ENERGY_PM, ENERGY_QP, ENERGY_QM, FREQUENCY, ACTIVE_POWER, REACTIVE_POWER, VOLTAGE, CURRENT };

  struct Meter {
    MeterModel model{METER_SEAB};
    std::string name;
    std::string address;
    uint32_t update_interval_ms{10000};
    uint32_t next_poll_ms{0};
    std::array<sensor::Sensor *, MEASUREMENT_COUNT> sensors{};
    binary_sensor::BinarySensor *connection_sensor{nullptr};
    text_sensor::TextSensor *last_success_sensor{nullptr};
    sensor::Sensor *error_counter_sensor{nullptr};
    uint32_t error_count{0};
    bool online{false};
    bool reading_succeeded{false};
    bool first_response_logged{false};
    uint8_t request_index{0};
    uint8_t retry_count{0};
    std::array<Request, MAX_REQUESTS> requests{};
    uint8_t request_count{0};
    std::string last_error;
  };

  void start_next_meter_();
  void start_session_();
  void build_request_list_();
  void start_next_request_();
  void send_text_(const std::string &frame, Expect expect, const char *stage);
  void send_binary_(std::string frame, Expect expect, const char *stage, bool add_bcc);
  void send_buffer_();
  void handle_tx_drain_();
  void read_uart_();
  bool capturing_first_response_() const;
  void log_first_response_(const char *result);
  void handle_response_();
  void handle_timeout_();
  void retry_or_fail_(const char *reason);
  void fail_meter_(const char *reason);
  void fail_request_(const char *reason);
  void finish_meter_(bool successful);
  void set_online_(Meter &meter, bool online);
  void record_error_(Meter &meter, const char *stage, const char *reason);
  void update_error_counter_(Meter &meter);
  bool process_measurement_(Meter &meter, Request request, const std::string &payload);
  void publish_(Meter &meter, Measurement measurement, float value);
  bool has_any_sensor_(const Meter &meter, std::initializer_list<Measurement> measurements) const;
  bool is_frame_complete_() const;
  bool validate_bcc_(const std::string &frame) const;
  std::string make_binary_frame_(const std::string &body) const;
  std::string current_meter_label_() const;
  static const char *model_name_(MeterModel model);
  static const char *request_name_(Request request);
  static bool parse_number_(const std::string &text, float *value);

  InternalGPIOPin *direction_pin_{nullptr};
  std::vector<Meter> meters_;
  uint32_t baud_rate_{4800};
  uint32_t response_timeout_ms_{500};
  uint8_t active_meter_index_{0};
  bool has_active_meter_{false};
  State state_{State::IDLE};
  Expect expect_{Expect::ADDRESS};
  Request active_request_{Request::ENERGY_PP};
  std::string active_stage_;
  std::array<uint8_t, RX_BUFFER_SIZE> rx_buffer_{};
  size_t rx_length_{0};
  bool debug_first_response_{false};
  std::array<uint8_t, RX_BUFFER_SIZE> debug_rx_buffer_{};
  size_t debug_rx_length_{0};
  std::array<uint8_t, 80> tx_buffer_{};
  size_t tx_length_{0};
  uint32_t tx_done_at_{0};
  uint32_t response_deadline_{0};
  std::string last_tx_frame_;
};

}  // namespace pozyton_energy_meters
}  // namespace esphome
