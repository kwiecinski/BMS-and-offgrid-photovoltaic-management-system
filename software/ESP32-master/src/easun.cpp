// Modbus RTU frame structure for Holding Registers:
//
// Request (Read Holding Registers - Function Code 0x03):
// +------------+--------------+----------------+----------------+----------------+----------------+
// | Server ID  | Function Code| Start Address  | Register Count | CRC (2 bytes)  |
// |   (1 byte) |   (1 byte)   |   (2 bytes)    |   (2 bytes)    |   (2 bytes)    |
// +------------+--------------+----------------+----------------+----------------+
//
// Response (Read Holding Registers):
// +------------+--------------+--------------+-------------------+----------------+
// | Server ID  | Function Code| Byte Count   | Register Data     | CRC (2 bytes)  |
// |   (1 byte) |   (1 byte)   |  (1 byte)    | (N x 2 bytes)     |   (2 bytes)    |
// +------------+--------------+--------------+-------------------+----------------+
//
// Example (reading 1 register at address 0x00CA):
// Request:  [0x01][0x03][0x00][0xCA][0x00][0x01][CRC_L][CRC_H]
// Response: [0x01][0x03][0x02][XX][YY][CRC_L][CRC_H]
// Where XXYY is the register value (XX=high byte, YY=low byte)

#define REGISTER_COUNT_201_220 20 // Number of registers to read starting from address 201

#include "easun.h"
enum class FrameIndex {
    ServerID_Index = 0,      // Server ID (slave address)
    FunctionCode_Index,      // Function code
    ByteCount_Index,         // Number of data bytes
    DataStart_Index,         // Start of data bytes   
};

enum class RegisterType {
    Holding,  // Holding register (0x03)
    Input     // Input register (0x04)
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




const char* outputPriorityOptions[] = {
  "UTI",  
  "SOL",   
  "SBU",
  "SUB",      
  nullptr    
};

static const char* outputModeOptions[] = {
  "Single",
  "Parallel", 
  "3 Phase-P1", 
  "3 Phase-P2", 
  "3 Phase-P3", 
  nullptr
};

static const char* inputVoltageRangeOptions[] = {
  "Wide range", 
  "Narrow range",
  nullptr
};

static const char* operationModeID[] = {
 "Power On",
 "Standby",
 "Mains",
 "Off-Grid",
 "Bypass",
 "Charging",
 "Fault",
  nullptr
};

static const char* buzzerModeOptions[] = {
    "Mute in all situations",
    "Sound on source change or warning/fault",
    "Sound on warning/fault",
    "Sound on fault only",
    nullptr
};

static const char* lcdBacklightOptions[] = {
    "Timed off", "Always on", nullptr
};

static const char* lcdReturnHomeOptions[] = {
    "Do not return automatically",
    "Automatically return after 1 minute",
    nullptr
};

static const char* energySavingModeOptions[] = {
    "Off", "On", nullptr
};

static const char* overloadRestartOptions[] = {
    "Do not restart after overload",
    "Restart automatically after overload",
    nullptr
};

static const char* overTempRestartOptions[] = {
    "Do not restart after over-temp",
    "Restart automatically after over-temp",
    nullptr
};

static const char* overloadToBypassOptions[] = {
    "Disable", "Enable", nullptr
};

static const char* batteryEqModeOptions[] = {
    "Disable", "Enable", nullptr
};

static const char* batteryChargingPriorityOptions[] = {
    "Utility priority", 
    "PV priority", 
    "PV = Utility", 
    "Only PV", 
    nullptr
};

static const char* turnOnModeOptions[] = {
    "Local or remote",
    "Only local",
    "Only remote",
    nullptr
};

static const char* remoteSwitchOptions[] = {
    "Remote shutdown",
    "Remote turn-on",
    nullptr
};

static const char* exitFaultOptions[] = {
    "-", // brak opcji dla 0
    "Exit fault state",
    nullptr
};

typedef struct{
    uint16_t faultCode;                // Fault code
    uint16_t warningCode;              // Warning code
    uint16_t operationModeID;          // Operation mode ID
    int16_t effectiveMainsVoltage;     // Effective mains voltage (V)
    int16_t mainsFrequency;            // Mains frequency (Hz)
    int16_t averageMainsPower;         // Average mains power (W)
    int16_t effectiveInverterVoltage;  // Effective inverter voltage (V)
    int16_t effectiveInverterCurrent;  // Effective inverter current (A)
    int16_t inverterFrequency;         // Inverter frequency (Hz)
    int16_t averageInverterPower;      // Average inverter power (W)
    int16_t inverterChargingPower;     // Inverter charging power (W)
    int16_t outputEffectiveVoltage;    // Output effective voltage (V)
    int16_t outputEffectiveCurrent;    // Output effective current (A)
    int16_t outputFrequency;           // Output frequency (Hz)
    int16_t outputActivePower;         // Output active power (W)
    int16_t outputApparentPower;       // Output apparent power (VA)
    int16_t batteryAverageVoltage;     // Battery average voltage (V)
    int16_t batteryAverageCurrent;     // Battery average current (A)
    int16_t batteryAveragePower;       // Battery average power (W)
    int16_t pvAverageVoltage;          // PV average voltage (V)
    int16_t pvAverageCurrent;          // PV average current (A)
    int16_t pvAveragePower;            // PV average power (W)
    int16_t pvChargingAveragePower;    // PV charging average power (W)
    int16_t loadPercentage;            // Load percentage (%)
    int16_t dcdcTemperature;           // DCDC temperature (°C)
    int16_t inverterTemperature;       // Inverter temperature (°C)
    uint16_t batteryStateOfCharge;     // Battery state of charge (%)
    int16_t inverterChargingAvgCurrent; // Inverter charging average current (A)    
    int16_t pvChargingAvgCurrent;      // PV charging average current (A)
    uint16_t outputMode;               // Output mode   
    uint16_t outputPriority;           // Output priority
    uint16_t inputVoltageRange;        // Input voltage range
    uint16_t buzzerMode;               // Buzzer mode
    uint16_t lcdBacklight;             // LCD backlight
    uint16_t lcdReturnHome;            // Auto return to homepage
    uint16_t energySavingMode;         // Energy-saving mode
    uint16_t overloadAutoRestart;      // Overload auto restart
    uint16_t overTempAutoRestart;      // Over-temp auto restart
    uint16_t overloadToBypass;         // Overload to bypass enabled
    uint16_t batteryEqMode;            // Battery equalization mode enabled
    uint16_t outputVoltage;            // Output voltage (V)
    uint16_t batteryOvervoltageProtectionPoint; // Battery overvoltage protection point (V)
    uint16_t maxChargingVoltage;       // Maximum charging voltage (V)
    uint16_t floatingChargingVoltage;  // Floating charging voltage (V)
    uint16_t batteryDischargeRecoveryMains; // Battery discharge recovery (mains)


}EasunData;


// Modbus requests to read data from Easun inverter
uint8_t requests[] = {
        {100, 1},        // fault code
        {108, 1},        // warning code
        {201, 20},       // 201–220
        {223, 5},        // 223–227
        {229, 1},        // battery state of charge
        {232, 1},        // battery average current
        {301, 1}         // output priority
    };


static const ModbusRegister easun_registers[] = {
  { "Fault code",                        100, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, nullptr },
  { "Warning code",                      108, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, nullptr },
  { "Operation mode ID",                 201, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, operationModeID},
  { "Effective mains voltage",           202, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "V",   false, nullptr },
  { "Mains frequency",                   203, RegisterType::Holding, ValueType::S_WORD, 0.01f,  "Hz",  false, nullptr },
  { "Average mains power",               204, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },
  { "Effective inverter voltage",        205, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "V",   false, nullptr },
  { "Effective inverter current",        206, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
  { "Inverter frequency",                207, RegisterType::Holding, ValueType::S_WORD, 0.01f,  "Hz",  false, nullptr },
  { "Average inverter power",            208, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },    //Positive numbers indicate inverter output, negative numbers indicate inverter input
  { "Inverter charging power",           209, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },
  { "Output effective voltage",          210, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "V",   false, nullptr },
  { "Output effective current",          211, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
  { "Output frequency",                  212, RegisterType::Holding, ValueType::S_WORD, 0.01f,  "Hz",  false, nullptr },
  { "Output active power",               213, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W", false, nullptr },
  { "Output apparent power",             214, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "VA",  false, nullptr },
  { "Battery average voltage",          215, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "V",   false, nullptr },
  { "Battery average current",          216, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
  { "Battery average power",            217, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },
  { "PV average voltage",               219, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "V",   false, nullptr },
  { "PV average current",               220, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
  { "PV average power",                 223, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },
  { "PV charging average power",        224, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "W",   false, nullptr },
  { "Load percentage",                  225, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "%",   false, nullptr },
  { "DCDC Temperature",                 226, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "°C",  false, nullptr },
  { "Inverter Temperature",             227, RegisterType::Holding, ValueType::S_WORD, 1.0f,   "°C",  false, nullptr },
  { "Battery state of charge",          229, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "%",   false, nullptr },
  { "Battery average current",          232, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
    { "Inverter charging avg current",    233, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
    { "PV charging avg current",          234, RegisterType::Holding, ValueType::S_WORD, 0.1f,   "A",   false, nullptr },
    { "Output mode",                      300, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, outputModeOptions },
  { "Output priority",                  301, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, outputPriorityOptions },
    { "Input voltage range",              302, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, inputVoltageRangeOptions },
    { "Buzzer mode",                      303, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, buzzerModeOptions },
    { "LCD backlight",                    305, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, lcdBacklightOptions },
    { "Auto return to homepage",          306, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, lcdReturnHomeOptions },        
    { "Energy-saving mode",               307, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, energySavingModeOptions },
    { "Overload auto restart",            308, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, overloadRestartOptions },
    { "Over-temp auto restart",           309, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, overTempRestartOptions },
    { "Overload to bypass enabled",       310, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, overloadToBypassOptions },
    {  "Battery Eq mode enabled",          313, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    false, batteryEqModeOptions },
    { "Output voltage",                            320, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Output frequency",                          321, RegisterType::Holding, ValueType::U_WORD, 0.01f,  "Hz",  true,  nullptr },
    { "Battery overvoltage protection point",      323, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Max charging voltage",                      324, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Floating charging voltage",                 325, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Battery discharge recovery (mains)",        326, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Battery low voltage protection (mains)",    327, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Battery low voltage protection (off-grid)", 329, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "V",   true,  nullptr },
    { "Battery charging priority",                 331, RegisterType::Holding, ValueType::U_WORD, 1.0f,   "",    true,  batteryChargingPriorityOptions },
    { "Maximum charging current",                  332, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "A",   true,  nullptr },
    { "Maximum mains charging current",            333, RegisterType::Holding, ValueType::U_WORD, 0.1f,   "A",   true,  nullptr },
    { "Eq Charging voltage",                       334, RegisterType::Holding, ValueType::U_WORD, 0.1f, "V",   true,  nullptr },
    { "Battery equalization time",                 335, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "min", true,  nullptr },
    { "Equalization timeout exit",                 336, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "min", true,  nullptr },
    { "Equalization charging interval",            337, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "day", true,  nullptr },
    {  "Turn on mode",                              406, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "",    true,  turnOnModeOptions },
    { "Remote switch",                             420, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "",    true,  remoteSwitchOptions },
    { "Exit the fault mode",                       426, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "",    false, exitFaultOptions },  
    { "Rated Power",                               643, RegisterType::Holding, ValueType::U_WORD, 1.0f,  "W",   false, nullptr }           
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
    // Checking minimul response lenght: 1B server ID + 1B function + 1B couter + N registers * 2 Bytes
    if (response.size() >= 3 + REGISTER_COUNT_201_220 * 2) {
        uint8_t byteCount;
        uint16_t value;

        response.get(static_cast<int>(FrameIndex::ByteCount_Index), byteCount);
        if (byteCount < REGISTER_COUNT_201_220 * 2) {
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
    Error err = client.addRequest(requestToken++, 1, READ_HOLD_REGISTER, 201, REGISTER_COUNT_201_220);
    if (err != SUCCESS) {
        ModbusError e(err);
        Serial.printf("Failed to send Modbus request: %02X - %s\n", (int)e, (const char *)e);
    }
}
