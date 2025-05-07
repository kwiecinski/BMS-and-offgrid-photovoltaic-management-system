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

#define MAX_CELL_VOLTAGE_DIFFRENCE 10     // tolerancja napi?cia mi?dzy ogniwami
#define MAX_CMP_VALUE       4000
#define STEP_12V         10
#define STEP_24V         10

#define PWM_24V_CMP_VAL     TCD0.CMPASET //off=4000
#define PWM_12V_CMP_VAL     TCD0.CMPBSET //off=0
#define KP      10
void balance_cells(void)
{

    uint16_t voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
    uint16_t voltage_batt_12V_low = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 10;
    uint16_t voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;

    int16_t cell_voltage_diffrence = (int16_t) voltage_batt_12V_high - (int16_t) voltage_batt_12V_low;

    uint16_t new_pwm_12V_cmp_val = PWM_12V_CMP_VAL, new_pwm_24V_cmp_val = PWM_24V_CMP_VAL;

    if (cell_voltage_diffrence > MAX_CELL_VOLTAGE_DIFFRENCE)
    {
        printf("pos delta \n\r");



        if ((PWM_24V_CMP_VAL-STEP_24V) < 0)
        {

        } else
        {
            new_pwm_24V_cmp_val = PWM_24V_CMP_VAL - STEP_24V;
            new_pwm_12V_cmp_val = 0;
        }

    } else if (cell_voltage_diffrence < -MAX_CELL_VOLTAGE_DIFFRENCE)
    {
        printf("neg delta \n\r");
        if ((PWM_12V_CMP_VAL + STEP_12V) >= 0)
        {
            new_pwm_12V_cmp_val = PWM_12V_CMP_VAL + STEP_12V;
            new_pwm_24V_cmp_val = MAX_CMP_VALUE;
        } else
        {

        }

    } else
    {
        // W zakresie tolerancji ? nic nie rób
        printf("ok delta \n\r");
        
        new_pwm_12V_cmp_val = 0;
        new_pwm_24V_cmp_val = MAX_CMP_VALUE;
    }

    // Zaktualizuj tylko je?li co? si? zmieni?o
    if (new_pwm_24V_cmp_val != PWM_24V_CMP_VAL || new_pwm_12V_cmp_val != PWM_12V_CMP_VAL)
    {

        printf("new_cmpa %u \n\r", new_pwm_12V_cmp_val);
        printf("new_cmpb %u \n\r", new_pwm_24V_cmp_val);
        while (!(TCD0.STATUS & TCD_CMDRDY_bm)); // wymagane!
        PWM_24V_CMP_VAL = new_pwm_24V_cmp_val;
        PWM_12V_CMP_VAL = new_pwm_12V_cmp_val;
        TCD0.CTRLE |= TCD_SYNC_bm;
        while (!(TCD0.STATUS & TCD_CMDRDY_bm));

    }
}



