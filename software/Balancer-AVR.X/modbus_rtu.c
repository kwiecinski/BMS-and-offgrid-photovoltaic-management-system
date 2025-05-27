#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "libraries/nanomodbus.h"


#define SLAVE_ADDRESS       0x10
#define BAUDRATE            9600
#define BITS_PER_CHAR       10 // 1 start + 8 data + 1 stop
#define READ_TIMEOUT_MS     1000
// teraz tworzysz serwer lub klienta:


void modbus_init(void)
{
    nmbs_t mb;
    
    nmbs_error err = nmbs_server_create(&mb, &conf, SLAVE_ADDRESS); // 0x01 to Twój adres slav
    
    float char_time_ms = 1000.0f * BITS_PER_CHAR / BAUDRATE;
    int byte_timeout_ms = (int)(1.5f * char_time_ms + 0.5f); // zaokr?glenie
    nmbs_set_byte_timeout(&mb, byte_timeout_ms);
    nmbs_set_read_timeout(&mb, READ_TIMEOUT_MS);  // np. 1000 ms (1 s) na odebranie ca?ej ramki
    
}


int32_t my_uart_read(uint8_t* buf, uint16_t count, int32_t timeout_ms, void* arg) {
    uint16_t received = 0;
    uint32_t start = millis(); // musisz mie? funkcj? zwracaj?c? millis

    while (received < count) {
        if (USART1_IsRxReady()) {
            buf[received++] = USART1_Read();
        } else if (millis() - start > timeout_ms) {
            break; // timeout
        }
    }

    return received; // mo?e by? < count ? to timeout
}

int32_t my_uart_write(const uint8_t* buf, uint16_t count, int32_t timeout_ms, void* arg) {
    uint16_t sent = 0;

    RS485_RX_SetHigh(); // TX enable

    while (sent < count) {
        if (USART1_IsTxReady()) {
            USART1_Write(buf[sent++]);
        }
        // opcjonalny timeout
    }

    while (!USART1_IsTxDone()); // poczekaj a? bufor si? opró?ni
    RS485_RX_SetLow(); // RX enable

    return sent;
}

nmbs_platform_conf conf = {
    .transport = NMBS_TRANSPORT_RTU,
    .read = my_uart_read,
    .write = my_uart_write,
    .crc_calc = NULL, // u?yj domy?lnej CRC
    .arg = NULL
};