#pragma once
#include <Arduino.h>
#include "ModbusClientRTU.h"

void initEasun(ModbusClientRTU& client, HardwareSerial& serial);
void requestEasunData(ModbusClientRTU& client);
