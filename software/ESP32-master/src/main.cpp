#include <Arduino.h>
#include "ModbusClientRTU.h"
#include "easun.h"

// Global Modbus client instance
ModbusClientRTU MB;

unsigned long lastReadTime = 0;
const unsigned long interval = 5000;

void setup() {
    Serial.begin(9600);
    while (!Serial) {}  // Wait for USB serial

    Serial.println("__ START __");

    // Initialize Easun Modbus client
    initEasun(MB, Serial2);
}

void loop() {
    if (millis() - lastReadTime >= interval) {
        lastReadTime = millis();
        requestEasunData(MB);
    }
}
