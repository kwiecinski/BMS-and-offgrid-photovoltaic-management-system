#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"

namespace itron
{

  class ItronComponent : public esphome::Component
  {
  public:
    explicit ItronComponent(esphome::uart::UARTComponent *uart) : uart_(uart) {}

    size_t receive_frame_()
    {
      uint32_t start_ms = millis();
      size_t ret_val = 0;

      while (this->uart_->available() > 0)
      {
        uint8_t c;
        if (!this->uart_->read_byte(&c))
        {
          break; // jeśli brak bajtu, wyjdź natychmiast
        }

        if (line_buffer_.length() < MAX_LINE_BUF)
        {
          if (c != '\r')
            line_buffer_ += (char)c;

          if (c == '\n')
          {
            // Sprawdź, czy linia zaczyna się od /ACE0
            if (line_buffer_.startsWith("/ACE0"))
            {
              uint8_t ack_byte[] = {0x06};
              this->uart_->write_array(ack_byte, 1); // natychmiastowy ACK
              this->uart_->write_str("000\r\n");     // reszta
            }

            line_buffer_ = "";
          }
        }
        else
        {
          line_buffer_ = ""; // reset bufora
        }

        // Zabezpieczenie czasu przetwarzania
        if (millis() - start_ms > 15)
        {
          break; // wychodzimy, żeby loop() się nie blokował
        }
      }

      return ret_val;
    }

    void setup() override
    {
      ESP_LOGI(TAG, "Itron component setup complete");
    }

    void loop() override
    {
      static uint32_t last_ms = 0;
      const uint8_t ack_byte[] = {0x06};
      // Wysyłamy komendę co 5 sekund
      if (millis() - last_ms > 10000)
      {
        this->uart_->write_str("/?!\r\n");
        ESP_LOGI(TAG, "Sent init command");
        last_ms = millis();

        while (millis() - last_ms < 1600)
        {
        };

        this->uart_->write_array(ack_byte, 1); // natychmiastowy ACK
        this->uart_->write_str("000\r\n");
        ESP_LOGI(TAG, "Sent ack");
      }

      // receive_frame_();  // nieblokujący odczyt i obsługa ACK
    }

  private:
    esphome::uart::UARTComponent *uart_{nullptr};
    String line_buffer_;
    static constexpr size_t MAX_LINE_BUF = 128;
    static constexpr const char *TAG = "itron";
  };

} // namespace itron
