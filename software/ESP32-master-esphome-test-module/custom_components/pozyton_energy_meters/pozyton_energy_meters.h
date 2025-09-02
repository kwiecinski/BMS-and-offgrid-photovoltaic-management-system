#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"
#include <string>
#include <vector>

class FrameBuilder;

namespace esphome
{
  namespace pozyton_energy_meters
  {

    struct ObisData
    {
      bool valid;        
      std::string obis; 
      std::string value;
      std::string unit; 
    };

    ObisData parse_measurment(const std::vector<uint8_t> &buffer);

    enum MeterType
    {
      METER_SEAB,
      METER_EABM,
    };

    class PozytonOBISSensor : public sensor::Sensor
    {
    public:
      void set_obis(const std::string &obis_code) { this->obis_ = obis_code; }
      const std::string &get_obis() const { return obis_; }
      void publish_measurement(const std::string &value, const std::string &unit)
      {
        this->publish_state(std::stod(value)); // publish numeric value
        this->unit_ = unit;
      }

    private:
      std::string obis_;
      std::string unit_;
    };

    class PozytonEnergyMeters : public PollingComponent, public uart::UARTDevice
    {
    public:

      void register_sensor(sensor::Sensor *sensor, const std::string &obis)
      {
        auto obis_sensor = static_cast<PozytonOBISSensor *>(sensor);
        obis_sensor->set_obis(obis);
        this->sensors_.push_back(obis_sensor);
      }
     
      void set_meter_type(MeterType type) { meter_type_ = type; } // setter function
      MeterType get_meter_type() const { return meter_type_; }
      void set_dir_pin(InternalGPIOPin *pin) { dir_pin_ = pin; }
      void set_debug(bool debug) { debug_ = debug; }

      void setup() override;
      void update() override;

      enum FrameType
      {
        FRAME_HANDSHAKE,
        FRAME_WORK_MODE,
        FRAME_REGISTER_MODE,
        FRAME_DATA
      };

      // --- added void return type ---
      void send_frame(const uint8_t *frame, size_t length);
      void calculate_bcc(FrameBuilder &fb);
      bool validate_frame(const std::vector<uint8_t> &buffer, FrameType type, const FrameBuilder *expected_fb = nullptr);

      bool read_raw_frame(std::vector<uint8_t> &buffer, uint32_t timeout_ms);

    protected:
      MeterType meter_type_;
      InternalGPIOPin *dir_pin_{nullptr};
      bool debug_{false};

      void send_init_sequence_();

      std::vector<PozytonOBISSensor *> sensors_;
    };

  } // namespace pozyton_energy_meters
} // namespace esphome
