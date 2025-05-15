#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "main.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "temp_regulator.h"

int16_t Get_Temperature_Celsius(uint16_t voltage_mv);

#define RESISTOR_DEVIDER_VAL_KOHM    100
#define REFRENCE_VOLTAGE             2500
#define TEMP_TABLE_START_C       -10
#define TEMP_TABLE_END_C         100
#define TEMP_TABLE_SIZE          (TEMP_TABLE_END_C - TEMP_TABLE_START_C + 1)

void temperature_regulator(void)
{

}

uint16_t calculate_temp(temperature temp)
{

    uint16_t thermistor_voltage, resistance;

    switch (temp)
    {
    case TEMP_BALANCER:
        thermistor_voltage = Get_ADC_Voltage(ADC_CHANNEL_TEMP_BALANCER);
        break;

    case TEMP_SMPS:
        thermistor_voltage = Get_ADC_Voltage(ADC_CHANNEL_TEMP_SMPS);
        break;
    case TEMP_BATT_12V:
        thermistor_voltage = Get_ADC_Voltage(ADC_CHANNEL_TEMP_BATT_12V);
        break;
    case TEMP_BATT_24V:
        thermistor_voltage = Get_ADC_Voltage(ADC_CHANNEL_TEMP_BATT_24V);
        break;
    default:

        break;
    }

    resistance = (RESISTOR_DEVIDER_VAL_KOHM * thermistor_voltage) / (REFRENCE_VOLTAGE - thermistor_voltage);

    for (uint8_t i = 0; i < TEMP_TABLE_SIZE; i++)
    {
        if (resistance >= ntc_resistance_table[i])
        {
            return (TEMP_TABLE_START_C + i);
        }
    }



    return TEMP_TABLE_END_C; // if lower than all, assume max temp
}


#define SERIES_RESISTOR_OHM      10000  // value of resistor in series with NTC
#define V_REF_MV                 2500   // reference voltage in mV used for the voltage divider

// Lookup table: NTC resistance (in ohms) for temperatures from -10 to 100 °C
const uint16_t ntc_resistance_table[TEMP_TABLE_SIZE] = {
    32650, // -10°C
    30500, // -9
    28520, // -8
    26680,
    24980,
    23390,
    21910,
    20530,
    19230,
    18010,
    16870, // 0°C
    15800,
    14800,
    13870,
    13010,
    12210,
    11480,
    10800,
    10170,
    9580,
    9030, // 10°C
    8510,
    8020,
    7550,
    7110,
    6690,
    6290,
    5920,
    5560,
    5220,
    4910, // 20°C
    4600,
    4310,
    4050,
    3790,
    3560,
    3330,
    3120,
    2920,
    2730,
    2560, // 30°C
    2400,
    2240,
    2100,
    1960,
    1830,
    1710,
    1590,
    1490,
    1390,
    1290, // 40°C
    1210,
    1130,
    1050,
    980,
    910,
    850,
    790,
    730,
    680,
    630, // 50°C
    590,
    550,
    510,
    480,
    450,
    420,
    390,
    370,
    340,
    320, // 60°C
    300,
    280,
    260,
    250,
    230,
    220,
    210,
    200,
    190,
    180, // 70°C
    170,
    160,
    150,
    140,
    130,
    120,
    115,
    110,
    105,
    100, // 80°C
    95,
    90,
    85,
    80,
    76,
    72,
    68,
    65,
    62,
    59, // 90°C
    56,
    53,
    50,
    48,
    46,
    44,
    42,
    40,
    38,
    36 // 100°C
};


