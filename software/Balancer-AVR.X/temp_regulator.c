#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "main.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "temp_regulator.h"

#define RESISTOR_DEVIDER_VAL_KOHM    100
#define REFRENCE_VOLTAGE             2500
#define TEMP_TABLE_START       -10
#define TEMP_TABLE_END        100
#define TEMP_TABLE_SIZE          (TEMP_TABLE_END - TEMP_TABLE_START + 1)


#define DAC_MAX_OUTPUT      4096
#define MINIMUM_FAN_ENABLE_TEMPERATURE      38
#define MINIMUM_FAN_DISABLE_TEMPERATURE      35
#define KP  
#define FAN_VCC     1200    //fan supply in mV
#define MINIMUM_FAN_WORKING_VOLTAGE  800    //in mV
#define MAXIMUM_TEMPERATURE     70    
uint16_t calculate_temp(temp_sensor temp);

// Lookup table: NTC resistance (in ohms/10) for temperatures from -10 to 100 °C
// i.e for -10oC resistance is 586100 ohm (need to multiplay value from table by 10)
// temperature values  calculated using the extended ?Steinhart and Hart? equation
const uint16_t ntc_resistance_table[TEMP_TABLE_SIZE] =
{
    58610, 55440, 52458, 49652, 47012, 44526, 42185, 39979, 37901, 35942, //-10...0
    34094, 32352, 30707, 29155, 27690, 26306, 24998, 23762, 22594, 21489, //0...10
    20445, 19456, 18521, 17635, 16796, 16001, 15249, 14535, 13859, 13217, //11...20
    12609, 12031, 11483, 10963, 10469, 10000, 9554, 9131, 8728, 8345, //21...30
    7981, 7634, 7305, 6991, 6692, 6408, 6137, 5879, 5633, 5398, //31...40
    5175, 4961, 4758, 4564, 4379, 4202, 4033, 3872, 3718, 3571, //41...50
    3431, 3296, 3168, 3045, 2928, 2816, 2708, 2605, 2507, 2413, //51...60
    2322, 2236, 2153, 2074, 1998, 1925, 1855, 1788, 1723, 1662, //61...70
    1602, 1546, 1491, 1439, 1389, 1340, 1294, 1249, 1206, 1165, //71...80
    1126, 1088, 1051, 1016, 982, 950, 918, 888, 859, 831, //81...90
    804, 778, 753, 729, 706, 684, 662, 641, 621, 602, 584, //91...100
};

void temperature_regulator(void)
{
    static uint16_t fan_start_flag = 0;
    uint16_t temp = calculate_temp(TEMP_SMPS);

    // DAC value corresponding to minimum voltage that can run fan
    uint16_t min_dac_output = (uint32_t)MINIMUM_FAN_WORKING_VOLTAGE * DAC_MAX_OUTPUT / FAN_VCC;

    if (temp >= MINIMUM_FAN_ENABLE_TEMPERATURE)
    {
        if (!fan_start_flag)
        {
            fan_start_flag = 1;
            DAC0_SetOutput(DAC_MAX_OUTPUT);   // Kick fan with 100%
            // Delay e.g. 3s ? implement this asynchronously!
        }
        else
        {
            // Proportional gain calculation
            uint16_t range_temp = MAXIMUM_TEMPERATURE - MINIMUM_FAN_ENABLE_TEMPERATURE;
            uint16_t error = temp - MINIMUM_FAN_DISABLE_TEMPERATURE;
            uint16_t range_dac = DAC_MAX_OUTPUT - min_dac_output;

            uint32_t dac_value = (uint32_t)error * range_dac / range_temp + min_dac_output;

            // Clamp to DAC_MAX_OUTPUT (safety, in case of overshoot)
            if (dac_value > DAC_MAX_OUTPUT)
            {
                dac_value = DAC_MAX_OUTPUT;
            }

            DAC0_SetOutput(dac_value);
        }
    }
    else if (temp < MINIMUM_FAN_DISABLE_TEMPERATURE)
    {
        fan_start_flag = 0;
        DAC0_SetOutput(0);  // Turn off fan
    }
}








}

uint16_t calculate_temp(temp_sensor temp)
{

    uint16_t thermistor_voltage = 0, resistance = 0;

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
            return (TEMP_TABLE_START + i);
        }
    }

    return TEMP_TABLE_END; // if lower than all, assume max temp
}





