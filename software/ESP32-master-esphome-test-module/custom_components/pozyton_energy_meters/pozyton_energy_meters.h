#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/hal.h"
#include <string>
#include <vector>

class FrameBuilder;


namespace esphome {
namespace pozyton_energy_meters {

enum MeterType {
  METER_SEAB,
  METER_EABM,
};

class PozytonEnergyMeters : public PollingComponent, public uart::UARTDevice {
 public:
  void set_meter_type(MeterType type) { meter_type_ = type; }
  void set_dir_pin(InternalGPIOPin *pin) { dir_pin_ = pin; }
  void set_debug(bool debug) { debug_ = debug; }

  void setup() override;
  void update() override;

  // --- added void return type ---
  void send_frame(const uint8_t *frame, size_t length);
  void calculate_bcc(FrameBuilder &fb);

 protected:
  MeterType meter_type_;
  InternalGPIOPin *dir_pin_{nullptr};
  bool debug_{false};

  void send_init_sequence_();
  std::vector<uint8_t> rx_buffer_;
};


}  // namespace pozyton_energy_meters
}  // namespace esphome
