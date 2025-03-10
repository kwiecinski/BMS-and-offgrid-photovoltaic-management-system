/* 
 * File:   adc_conv.h
 * Author: RaD
 *
 * Created on 7 grudnia 2022, 09:00
 */

#ifndef ADC_CONV_H
#define	ADC_CONV_H

#ifdef	__cplusplus
extern "C" {
#endif


#define ADC_CHANNEL_VDD_DIV10           ADC_MUXPOS_VDDDIV10_gc
#define ADC_CHANNEL_12V_BATT            01
#define ADC_CHANNEL_TEMP_BATT_12V       29
#define ADC_CHANNEL_TEMP_BATT_24V       02
#define ADC_CHANNEL_TEMP_SMPS           06
#define ADC_CHANNEL_VREF                07
    
uint16_t Get_ADC_Voltage(adc_0_channel_t channel);
    

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_CONV_H */

