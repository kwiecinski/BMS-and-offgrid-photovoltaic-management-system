/*
 * File:   adc.c
 * Author: User
 *
 * Created on 14 listopada 2024, 21:02
 */


#include <xc.h>
#include "main.h"
#include <stdio.h>

void ADC_Init(void) 
{
    // Select ADC conversion clock (FOSC/32 for 8 MHz clock)
    ADCON0bits.ADCS = 0b10;  // ADC clock source FOSC/32

    // Configure voltage reference to use Vref+ on RA3 and Vss as Vref-
    ADCON1bits.VCFG0 = 1;    // Vref+ set to external reference (RA3)
    ADCON1bits.VCFG1 = 0;    // Vref- set to Vss (ground)

    // Select ADC input channel AN0 (RA0)
    ADCON0bits.CHS = 0b0000;  // Channel Select bits (AN0)
   __delay_ms(2);
   
   
    // Configure result format as right justified
    ADCON1bits.ADFM = 1;     // Result is right justified

    // Turn on ADC module
    ADCON0bits.ADON = 1;     // ADC enable bit
}

unsigned int ADC_Read_ADC_Result(void) 
{
    unsigned int adcResult;


    // Start conversion
    ADCON0bits.GO_nDONE = 1;

        // Wait until conversion is complete
    while(ADCON0bits.GO_nDONE);

    // Read ADC result
    adcResult = ((ADRESH << 8) + ADRESL);  // Combine high and low result bytes

    // Sta?a skaluj?ca na podstawie Vref (2,467V) oraz dzielnika 6,8k? i 1,3k?
    // scaledVoltage = (adcResult * 2467 * (6800 + 1300)) / (1300 * 1023 * 10)
    // Sta?a po uproszczeniu wynosi 51

    return (unsigned int)adcResult;  // Return result in format 247 for 2.47V
}


uint16_t ReadVoltageAverage() {
    uint32_t sum = 0;  // Sum of all samples
    uint16_t sample;
    
    uint32_t R1 = 6960;
    uint32_t R2 = 1000;
    
    
    const unsigned long vref=2500;
    
    const uint8_t num_samples = 20;

    for (uint8_t i = 0; i < num_samples; i++) {
        sample = ADC_Read_ADC_Result();  // Function to read a single ADC result
        sum += sample;

        __delay_ms(1);  // Small delay between samples for stabilization
    }

    uint32_t average = (uint16_t)(sum / num_samples);  // Calculate the average

   average =  average*10000;
   average =  average/1023;
   average = average * vref;
   average = average/10000;
   
  // printf("average: %u \n\r",average);
   
   R1=R1*1000;
   R1=1000000+R1;
   R1=R1/R2;
///   printf("r1: %u \n\r",R1);
   average = average * R1;
   average = average/10000;
    // Convert to voltage (assuming scaling is already set in the ReadADC function)
    // In this example, we assume the ADC result directly represents millivolts.

    return average;
}


unsigned int DisplayVoltage(void) 
{
    unsigned int voltage = ReadVoltageAverage() ;
    
    if (voltage%100 < 10) 
    {
        printf("12V Batt Voltage: %d.0%dV \r\n", voltage / 100, voltage % 100);  // Dodaje zero wiod?ce
    } else 
    {
        printf("12V Batt voltage  Voltage: %d.%dV \r\n", voltage / 100, voltage % 100);
    }
        
    return voltage;
   /*
    if (voltage%100 < 10) 
    {
        printf("12V Batt Voltage: %d.0%dV \r\n", voltage / 100, voltage % 100);  // Dodaje zero wiod?ce
    } else 
    {
        printf("12V Batt Voltage: %d.%dV \r\n", voltage / 100, voltage % 100);
    }
    */
}
