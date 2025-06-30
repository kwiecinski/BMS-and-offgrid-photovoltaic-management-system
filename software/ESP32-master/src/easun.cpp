#include "easun.h"
enum class FrameIndex {
    ServerID_Index = 0,      // Server ID (slave address)
    FunctionCode_Index,      // Function code
    ByteCount_Index,         // Number of data bytes
    DataStart_Index,         // Start of data bytes   
};

enum class RegisterType {
    Holding,
    Input
};

enum class ValueType {
    S_WORD,  // signed int16_t
    U_WORD   // unsigned uint16_t
};

struct ModbusRegister {
    const char* name;                        // Register description
    uint16_t address;                        // Modbus register address
    RegisterType reg_type;                   // Holding/Input
    ValueType value_type;                    // S_WORD / U_WORD
    float multiplier;                        // Conversion multiplier
    const char* unit;                        // Unit like V, W, A, etc.
    bool writable;                           // Can be written by master
    const char** enum_options;               // Optional list of string values (for modes)
};


const char* outputPriorityModes[] = {
  "UTI",  
  "SOL",   
  "SBU",
  "SUB",      
  nullptr    
};

// Tablica z rejestrami do odczytu
const ModbusRegister easun_registers[] = {
    { "PV average voltage",       219, RegisterType::Holding, ValueType::S_WORD, 0.1f, "V", false, nullptr },
    { "PV average current",       221, RegisterType::Holding, ValueType::S_WORD, 0.1f, "A", false, nullptr },
    { "Battery voltage",           200, RegisterType::Holding, ValueType::S_WORD, 0.1f, "V", false, nullptr },
    { "Battery current",           201, RegisterType::Holding, ValueType::S_WORD, 0.1f, "A", false, nullptr },
    { "Battery temperature",       202, RegisterType::Holding, ValueType::S_WORD, 0.1f, "C", false, nullptr },
    { "Battery capacity",          203, RegisterType::Holding, ValueType::U_WORD, 1.0f, "%", false, nullptr },
    { "Battery SOC",               204, RegisterType::Holding, ValueType::U_WORD, 1.0f, "%", false, nullptr },
    { "Battery voltage setpoint",  205, RegisterType::Holding, ValueType::S_WORD, 0.1f, "V", true , nullptr},
    { "Battery current setpoint",  206, RegisterType::Holding, ValueType::S_WORD, 0.1f,"A", true , nullptr},
    { "Battery charge mode",       207, RegisterType::Holding, ValueType::U_WORD, 1.0f," ", true , nullptr},
    { "Battery discharge mode",    208, RegisterType::Holding, ValueType::U_WORD, 1.0f," ", true , nullptr},
    { "Output voltage setpoint",   209, RegisterType::Holding, ValueType::S_WORD, 0.1f,"V", true , nullptr},
    { "Output frequency setpoint", 210, RegisterType::Holding, ValueType::S_WORD ,0.01f,"Hz",true ,nullptr},
    { "Output active power limit", 211, RegisterType::Holding ,ValueType::S_WORD ,1.0f,"W" ,true ,nullptr},
    { "Output active power",      213, RegisterType::Holding, ValueType::S_WORD, 1.0f, "W", false, nullptr },
    { "PV average power",         223, RegisterType::Holding, ValueType::S_WORD, 1.0f, "W", false, nullptr },
    { "Battery average voltage",  215, RegisterType::Holding, ValueType::S_WORD, 0.1f, "V", false, nullptr},
    { "Output priority",          301, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "", true, outputPriorityModes},

};


// Token for Modbus requests
static uint32_t requestToken = 1;

// Callback to handle received Modbus data
void handleEasunData(ModbusMessage response, uint32_t token) {
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
            Serial.printf("Effective mains voltage: %.1f V\n", voltage);
        } else {
            Serial.printf("Unexpected byte count: %d\n", byteCount);
        }
    } else {
        Serial.println("Too short Modbus response.");
    }
}

// Callback to handle Modbus errors
void handleEasunError(Error error, uint32_t token) {
    ModbusError me(error);
    Serial.printf("Modbus error: %02X - %s\n", (int)me, (const char *)me);
}

// Initialize Easun Modbus communication
void initEasun(ModbusClientRTU& client, HardwareSerial& serial) {
    RTUutils::prepareHardwareSerial(serial);
    serial.begin(9600, SERIAL_8N1, 4, 5);  // RX=4, TX=5
    client.begin(serial);
    client.setTimeout(2000);
    client.onDataHandler(&handleEasunData);
    client.onErrorHandler(&handleEasunError);
}

// Periodic request to Easun inverter
void requestEasunData(ModbusClientRTU& client) {
    Error err = client.addRequest(requestToken++, 1, READ_HOLD_REGISTER, 202, 1);
    if (err != SUCCESS) {
        ModbusError e(err);
        Serial.printf("Failed to send Modbus request: %02X - %s\n", (int)e, (const char *)e);
    }
}
