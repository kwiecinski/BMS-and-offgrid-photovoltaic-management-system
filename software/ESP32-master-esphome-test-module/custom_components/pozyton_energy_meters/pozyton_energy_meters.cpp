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

FrameBuilder make_handshake_response()
{
  FrameBuilder fb;
  fb.add_ascii("EABM");
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

    bool PozytonEnergyMeters::read_raw_frame(std::vector<uint8_t> &buffer, uint32_t timeout_ms = 500)
    {
      buffer.clear();
      uint32_t start = millis();
      bool started = false; // czy zaczęliśmy odbierać dane

      while (millis() - start < timeout_ms)
      {
        while (this->available())
        {
          uint8_t c;
          this->read_byte(&c);
          if (!started)
          {
            if (c == 0x00)
              continue; // ignorujemy wiodące zero
            else
              started = true;
          }
          buffer.push_back(c);

          if (buffer.size() > 512)
          {
            buffer.clear();
            ESP_LOGW(TAG, "RX buffer overflow, cleared");
          }
        }
      }
      return !buffer.empty();
    }

    void log_buffer(const std::vector<uint8_t> &buffer, const char *tag = "POZYTON")
    {
      std::string s;
      for (auto b : buffer)
      {
        if (b >= 32 && b <= 126)
          s += (char)b; // drukowalne znaki ASCII
        else
        {
          char buf[5];
          sprintf(buf, "%02X ", b); // nie drukowalne jako hex
          s += buf;
        }
      }
      ESP_LOGI(tag, "Buffer: %s", s.c_str());
    }

    // Funkcja walidująca ramkę w zależności od typu
    bool PozytonEnergyMeters::validate_frame(const std::vector<uint8_t> &buffer, FrameType type, const FrameBuilder *expected_fb)
    {
      if (buffer.empty())
        return false;

      switch (type)
      {
      case FRAME_HANDSHAKE:
        // szukamy końca LF i ciągu "EABM"
        for (auto b : buffer)
        {
          if (b == LF)
            break;
        }
        for (size_t i = 0; i + 3 < buffer.size(); i++)
        {
          if (buffer[i] == 'E' && buffer[i + 1] == 'A' && buffer[i + 2] == 'B' && buffer[i + 3] == 'M')
          {
            return true;
          }
        }
        return false;

      case FRAME_WORK_MODE:
      case FRAME_DATA:
      {
        log_buffer(buffer, TAG);
        if (buffer.size() < 3)
        { // minimalna ramka: STX + ETX + BCC
          ESP_LOGW(TAG, "min frame");
          return false;
        }

        if (buffer[0] != STX)
        {
          ESP_LOGW(TAG, "stx error");
          return false;
        }

        size_t etx_index = buffer.size() - 2; // przedostatni bajt to ETX
        uint8_t received_bcc = buffer.back(); // ostatni bajt = BCC

        if (buffer[etx_index] != ETX)
        {
          ESP_LOGW(TAG, "etx error");
          return false;
        }

    // Oblicz BCC od drugiego bajtu do bajtu przed ETX (STX pominięte)
    uint8_t bcc_calc = 0;
    for (size_t i = 1; i <= etx_index; i++)
        bcc_calc ^= buffer[i];

    if (bcc_calc != received_bcc)
    {
        ESP_LOGW(TAG, "bcc mismatch: calculated=0x%02X, received=0x%02X", bcc_calc, received_bcc);
        return false;
    }

    return true; // ramka DATA poprawna
      }

      case FRAME_REGISTER_MODE:
        // oczekujemy ACK lub NAK
        for (auto b : buffer)
        {
          if (b == ACK)
            return true;
          if (b == NAK)
            return false;
        }
        return false;

      default:
        return false;
      }
    }

    void PozytonEnergyMeters::send_init_sequence_()
    {

      std::vector<uint8_t> rx_buf;

      FrameBuilder fb_handshake = make_handshake();
      send_frame(fb_handshake.data(), fb_handshake.size());

      if (read_raw_frame(rx_buf))
      {
        if (validate_frame(rx_buf, FRAME_HANDSHAKE))
        {
          ESP_LOGI(TAG, "Handshake OK");
        }
        else
        {
          ESP_LOGW(TAG, "Handshake failed");
        }
      }

      FrameBuilder fb_work = make_work_mode();
      calculate_bcc(fb_work);
      send_frame(fb_work.data(), fb_work.size());

      if (read_raw_frame(rx_buf))
      {
        if (validate_frame(rx_buf, FRAME_WORK_MODE))
        {
          ESP_LOGI(TAG, "Work mode OK");
        }
        else
        {
          ESP_LOGW(TAG, "Work mode failed");
        }
      }

      FrameBuilder fb_register_mode = make_register_mode();
      calculate_bcc(fb_register_mode); // add BCC
      send_frame(fb_register_mode.data(), fb_register_mode.size());

      if (read_raw_frame(rx_buf))
      {
        if (validate_frame(rx_buf, FRAME_REGISTER_MODE))
        {
          ESP_LOGI(TAG, "register mode OK");
        }
        else
        {
          ESP_LOGW(TAG, "register mode failed");
        }
      }

      FrameBuilder fb_active_energy = make_active_energy_consumed();
      calculate_bcc(fb_active_energy); // add BCC
      send_frame(fb_active_energy.data(), fb_active_energy.size());

      if (read_raw_frame(rx_buf))
      {
        if (validate_frame(rx_buf, FRAME_DATA))
        {
          ESP_LOGI(TAG, "data OK");
        }
        else
        {
          ESP_LOGW(TAG, "data failed");
        }
      }

      FrameBuilder fb_exit_register = make_exit_register_mode();
      calculate_bcc(fb_exit_register); // add BCC
      send_frame(fb_exit_register.data(), fb_exit_register.size());

      if (read_raw_frame(rx_buf))
      {
        if (validate_frame(rx_buf, FRAME_REGISTER_MODE))
        {
          ESP_LOGI(TAG, "end register mode OK");
        }
        else
        {
          ESP_LOGW(TAG, "end register mode failed");
        }
      }

      ESP_LOGI(TAG, "Send request to energy meter");
    }
  }
}