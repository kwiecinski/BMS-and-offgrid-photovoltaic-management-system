#include "pozyton_energy_meters.h"
#include "esphome/core/log.h"
#include <string>
#include <vector>

#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define ACK 0x06
#define NAK 0x15
#define CR 0x0D
#define LF 0x0A

class FrameBuilder
{
  std::string frame_;

public:
  void clear() { frame_.clear(); }
  void add_byte(uint8_t b) { frame_.push_back(b); }
  void add_ascii(const char *s) { frame_ += s; }

  const uint8_t *data() const { return reinterpret_cast<const uint8_t *>(frame_.data()); }
  size_t size() const { return frame_.size(); }
};

FrameBuilder make_handshake()
{
  FrameBuilder fb;
  fb.add_ascii("/?000 0000000!\r\n");
  return fb;
}

FrameBuilder make_work_mode()
{
  FrameBuilder fb;
  fb.add_byte(ACK);
  fb.add_ascii("041");
  fb.add_byte(CR);
  fb.add_byte(LF);
  return fb;
}

FrameBuilder make_register_mode()
{
  FrameBuilder fb;
  fb.add_byte(SOH);
  fb.add_ascii("P1");
  fb.add_byte(STX);
  fb.add_ascii("()");
  fb.add_byte(ETX);
  return fb;
}

FrameBuilder make_active_energy_consumed()
{
  FrameBuilder fb;
  fb.add_byte(SOH);
  fb.add_ascii("R1");
  fb.add_byte(STX);
  fb.add_ascii("EPP0()");
  fb.add_byte(ETX);
  return fb;
}

FrameBuilder make_exit_register_mode()
{
  FrameBuilder fb;
  fb.add_byte(SOH);
  fb.add_ascii("B0");
  fb.add_byte(ETX);
  return fb;
}

namespace esphome
{
  namespace pozyton_energy_meters
  {

    static const char *const TAG = "pozyton_energy_meters";

    void PozytonEnergyMeters::setup()
    {
      if (this->dir_pin_ != nullptr)
      {
        this->dir_pin_->setup();              // configure pin as output
        this->dir_pin_->digital_write(false); // default = RX
      }
    }

    void PozytonEnergyMeters::update()
    {
      // Example: send init sequence every update interval
      this->send_init_sequence_();
    }

    void PozytonEnergyMeters::send_frame(const uint8_t *frame, size_t length)
    {
      if (this->dir_pin_ != nullptr)
      {
        this->dir_pin_->digital_write(true);
      }

      this->write_array(frame, length);
      this->parent_->flush();

      if (this->dir_pin_ != nullptr)
      {
        this->dir_pin_->digital_write(false);
      }
    }

    void PozytonEnergyMeters::calculate_bcc(FrameBuilder &fb)
    {
      uint8_t bcc = 0;
      const uint8_t *data = fb.data();
      size_t len = fb.size();

      for (size_t i = 1; i < len; i++)
        bcc ^= data[i]; // XOR wszystkich bajtów

      fb.add_byte(bcc); // dodajemy BCC na końcu ramki
    }

    void PozytonEnergyMeters::send_init_sequence_()
    {

      FrameBuilder fb_handshake = make_handshake();
      send_frame(fb_handshake.data(), fb_handshake.size());
      delay(300);  // wait for meter to process


      FrameBuilder fb_work = make_work_mode();
      calculate_bcc(fb_work); 
      send_frame(fb_work.data(), fb_work.size());
      delay(300);

      FrameBuilder fb_register_mode = make_register_mode();
      calculate_bcc(fb_register_mode);                     // add BCC
      send_frame(fb_register_mode.data(), fb_register_mode.size());
      delay(300);


      FrameBuilder fb_active_energy = make_active_energy_consumed();
      calculate_bcc(fb_active_energy);                     // add BCC
      send_frame(fb_active_energy.data(), fb_active_energy.size());
      delay(300);

      FrameBuilder fb_exit_register = make_exit_register_mode();
      calculate_bcc(fb_exit_register);                     // add BCC
      send_frame(fb_exit_register.data(), fb_exit_register.size());

      ESP_LOGI(TAG, "Send request to energy meter");
    }
  }
}