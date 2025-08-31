#include "pozyton_energy_meters.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pozyton_energy_meters {

static const char *const TAG = "pozyton_energy_meters";

void PozytonEnergyMeters::setup() {
  if (this->dir_pin_ != nullptr) {
    this->dir_pin_->setup();      // configure pin as output
    this->dir_pin_->digital_write(false);  // default = RX
  }
}

void PozytonEnergyMeters::update() {
  // Example: send init sequence every update interval
  this->send_init_sequence_();
  this->handle_rx_();
}

void PozytonEnergyMeters::send_init_sequence_() {

  const char *cmd = nullptr;

  if (this->meter_type_ == METER_SEAB) {
    cmd = "/A000.0000000\r\n";
  } else if(this->meter_type_ == METER_EABM){
    cmd = "/?000 0000000!\r\n";
  }

  if (this->dir_pin_ != nullptr) {
    this->dir_pin_->digital_write(true);   // TX mode
    delay(1);
  }

  this->write_str(cmd);
  ESP_LOGD(TAG, "Sent request: %s", cmd);

   if (this->parent_ != nullptr) {
    this->parent_->flush();  // ensure TX buffer is empty
  }

  if (this->dir_pin_ != nullptr) {
    delay(1);
    this->dir_pin_->digital_write(false);  // back to RX
  }
  ESP_LOGI(TAG, "Init sequence sent");
}

void PozytonEnergyMeters::handle_rx_() {
  while (this->available()) {
    uint8_t c;
    this->read_byte(&c);

    // Add byte to buffer
    rx_buffer_.push_back(c);

    // Check for end of frame
    if (c == '\n') {  // or '\r' depending on meter
      if (this->debug_) {
        std::string s;
        for (auto b : rx_buffer_) {
          if (b >= 32 && b <= 126) {
            s += (char)b;   // printable ASCII
          } else {
            s += '.';       // non-printable -> .
          }
        }
        ESP_LOGI(TAG, "RX frame: %s", s.c_str());
      }
      rx_buffer_.clear();
    }

    // Prevent buffer overflow
    if (rx_buffer_.size() > 512) {
      rx_buffer_.clear();
      ESP_LOGW(TAG, "RX buffer overflow, cleared");
    }
  }
}



}  // namespace pozyton_energy_meters
}  // namespace esphome
