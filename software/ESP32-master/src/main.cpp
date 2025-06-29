#include <Arduino.h>
#include "ModbusClientRTU.h"

// Modbus RTU client (ESP32 acts as master)
ModbusClientRTU MB;

// RS232 pin definitions
#define MODBUS_TX 5
#define MODBUS_RX 4

// Token for identifying requests
uint32_t Token = 1;

// Callback to handle received Modbus data
void handleData(ModbusMessage response, uint32_t token) {
  Serial.printf("Response: serverID=%d, FC=%d, Token=%08X, length=%d:\n", 
                response.getServerID(), response.getFunctionCode(), token, response.size());

  for (auto& byte : response) {
    Serial.printf("%02X ", byte);
  }
  Serial.println();

  if (response.size() >= 5) {
    uint8_t byteCount;
    uint16_t value;

    response.get(2, byteCount);     
    if (byteCount == 2) {
      response.get(3, value);       
      float voltage = value / 10.0; 
      Serial.printf("Voltage: %.1f V\n", voltage);
    } else {
      Serial.printf("Unexpected byte count: %d\n", byteCount);
    }
  } else {
    Serial.println("Too short response");
  }
}

// Callback to handle Modbus errors
void handleError(Error error, uint32_t token)
{
  ModbusError me(error);
  Serial.printf("Modbus error: %02X - %s\n", (int)me, (const char *)me);
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  } // Wait for USB serial connection
  Serial.println("__ START __");

  // Initialize hardware Serial2 for Modbus communication
  RTUutils::prepareHardwareSerial(Serial2);
  Serial2.begin(9600, SERIAL_8N1, MODBUS_RX, MODBUS_TX);

  // Configure Modbus client
  MB.begin(Serial2);
  MB.setTimeout(2000);
  MB.onDataHandler(&handleData);
  MB.onErrorHandler(&handleError);

}
unsigned long lastReadTime = 0;
const unsigned long interval = 5000;
void loop()
{

  if (millis() - lastReadTime >= interval)
  {
    lastReadTime = millis();
    Serial.printf("test \n");
    // Send request to read register 202 (1 word = 2 bytes)
    Error err = MB.addRequest(Token++, 1, READ_HOLD_REGISTER, 202, 1);
    if (err != SUCCESS)
    {
      ModbusError e(err);
      Serial.printf("Failed to create Modbus request: %02X - %s\n", (int)e, (const char *)e);
    }
  }
}
