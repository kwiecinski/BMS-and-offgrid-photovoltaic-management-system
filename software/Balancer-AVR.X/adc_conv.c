#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "adc_conv.h"

#define INTERNAL_VDD_CHANNEL_DIVIDER    10
#define BATT_12V_VOLTAGE_DIVIDER        782      //measured using multimeter
#define ADC_RESOLUTION_12BIT            4096
#define REFRENCE_VOLTAGE                2503    //measured using multimeter
#define SAMPLE_ACCUMULATION_NUMBER      16      //see datasheet

void print_voltage(const char *label, uint16_t result);

uint16_t Get_ADC_Voltage(adc_0_channel_t channel) 
{

    unsigned long int result;

    result = ADC0_GetConversion(channel);
    result = (result / SAMPLE_ACCUMULATION_NUMBER);
    // multiply and divide by 100 to avoid working on floats
    result = (result * REFRENCE_VOLTAGE * 100) / ADC_RESOLUTION_12BIT;
    result = result / 100;
    // result after calculations: 2462 = 2,462V
    
    //printf("RAW RESULT: %u \n",  result); 
    
    if (channel == ADC_CHANNEL_VDD_DIV10) 
    {
        result = result*INTERNAL_VDD_CHANNEL_DIVIDER;
        
    }else if (channel == ADC_CHANNEL_12V_BATT) 
    {
        result = (result * BATT_12V_VOLTAGE_DIVIDER) / 100; 
    }
    
    return (uint16_t) result;
}

void print_voltage(const char *label, uint16_t result) 
{
    printf("%s: %u.%02uV\n\r", label, result / 1000, (result / 10) % 100);
}


