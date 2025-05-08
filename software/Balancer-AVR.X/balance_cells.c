/*
 * File:   balance_cells.c
 * Author: User
 *
 * Created on 7 maja 2025, 20:43
 */

#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "inits.h"


#define MAX_CELL_VOLTAGE_DIFFRENCE  10
#define MAX_CMP_VALUE               4000    
#define PWM_24V_CMP_REGISTER        TCD0.CMPASET    // off=MAX_CMP_VALUE
#define PWM_12V_CMP_REGISTER        TCD0.CMPBSET    // off=0
#define KP                          10
#define MINIMUM_CELL_VOLTAGE        1200 
#define MAX_CELL_VOLTAGE_ERROR_DIFFERENCE 3000


void set_pwm(uint16_t set_12V_batt_pwm, uint16_t set_24V_batt_pwm)
{
    
    if (set_12V_batt_pwm > MAX_CMP_VALUE)
    {
        set_12V_batt_pwm = MAX_CMP_VALUE;
        
    }
    
    if (set_24V_batt_pwm > MAX_CMP_VALUE)
    {
        set_24V_batt_pwm = MAX_CMP_VALUE;  
    }
 
    while (!(TCD0.STATUS & TCD_CMDRDY_bm)); // CMDRDY == 1
    
    PWM_24V_CMP_REGISTER = MAX_CMP_VALUE - set_24V_batt_pwm;
    PWM_12V_CMP_REGISTER = set_12V_batt_pwm;

    TCD0.CTRLE |= TCD_SYNC_bm;
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
}


void balance_cells(void)
{

    //voltages are in format i.e: 1253 -> 12.53V, 546 -> 5,46V
    
    uint16_t voltage_bus = AutoFox_INA226_GetBusVoltage_V(&ina226);
    uint16_t voltage_batt_12V = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 10;     //devide by 10 to get desired resolution, the same as voltage_bus
    uint16_t voltage_batt_24V = voltage_bus - voltage_batt_12V;

    
    int16_t cell_voltage_diffrence = (int16_t)voltage_batt_12V  - (int16_t)voltage_batt_24V;     //calculating voltage difference between batteries
    
    uint16_t pwm_val = KP * abs(cell_voltage_diffrence);
    
    if (pwm_val > MAX_CMP_VALUE) 
    {
        pwm_val = MAX_CMP_VALUE;
    }
    
    if (abs(cell_voltage_diffrence) < MAX_CELL_VOLTAGE_ERROR_DIFFERENCE)
    {
        if(voltage_batt_12V >  MINIMUM_CELL_VOLTAGE && voltage_batt_24V >  MINIMUM_CELL_VOLTAGE)
        {
            if(cell_voltage_diffrence < 0)  //if true then voltage for battery 24V has higher voltage, and we need to load this cell
            {
                 set_pwm(0,pwm_val);
            }else   //need to load 12V cell
            {
                 set_pwm(pwm_val,0);
            } 
        }
    }else
    {
        // TODO: add error return code    
    }  
}



void disable_balancer_12V_WOB_output(void)
{
    TCD0.FAULTCTRL &= ~TCD_CMPBEN_bm; //zero bit disable WOB
    BALANCE_12V_SetHigh();
}

void disable_balancer_24V_WOB_output(void)
{
    TCD0.FAULTCTRL &= ~TCD_CMPAEN_bm; //zero bit disable WOB
    BALANCE_24V_SetHigh();
}

void enable_balancer_12V_WOB_output(void)
{
    TCD0.CMPBSET = TCD0.CMPBCLR;
    TCD0.FAULTCTRL |= TCD_CMPBEN_bm;
}