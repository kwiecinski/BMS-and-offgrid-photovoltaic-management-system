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
      bool valid;        // true jeśli parsowanie się udało
      std::string obis;  // np. "1.8.0"
      std::string value; // np. "004418.49"
      std::string unit;  // np. "kWh"
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

      void register_sensor(PozytonOBISSensor *sensor, const std::string &obis) {
    sensor->set_obis(obis);          // ustawienie OBIS w sensorze
    this->sensors_.push_back(sensor); // dodanie do listy hub’a

      }
      void set_meter_type(MeterType type) { meter_type_ = type; }
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

     std::vector<PozytonOBISSensor*> sensors_;
    
    };

  } // namespace pozyton_energy_meters
} // namespace esphome
