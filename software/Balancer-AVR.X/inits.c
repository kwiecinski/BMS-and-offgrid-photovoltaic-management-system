#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "interrupts.h"

#define MAX_CMP_VALUE               4000   



void ina266_init(void)
{

    AutoFox_INA226_Constructor(&ina226);
    SendErrorStatus(AutoFox_INA226_Init(&ina226, INA226_DEFAULT_I2C_ADDRESS, 100, 5));
    SendErrorStatus(AutoFox_INA226_ConfigureVoltageConversionTime(&ina226, 0b111)); //sample time 8.244ms
    SendErrorStatus(AutoFox_INA226_ConfigureNumSampleAveraging(&ina226, 0b010));

}

void balancer_timer_tcd_init(void)
{
    /*
     * The WOA output is set when the TCD counter counts down and matches the CMPASET value. WOA is cleared when
     * the TCD counter counts up and matches the CMPASET value.
     * The WOB output is set when the TCD counter counts up and matches the CMPBSET value. WOB is cleared when
     * the TCD counter counts down and matches the CMPBSET value.
     * 
     * The outputs will overlap if CMPASET > CMPBSET.
     * CMPACLR is not used in Dual Slope mode. Writing a value to CMPACLR has no effect.
     * 
     */

    while (!(TCD0.STATUS & TCD_CMDRDY_bm));

    TCD0.CMPBCLR = MAX_CMP_VALUE; //main tcd counter in dual slope
    TCD0.CMPBSET = 0;
    TCD0.CMPASET = MAX_CMP_VALUE; //WOA is cleared when the TCD counter counts up and matches the CMPASET value.

    TCD0.CTRLE |= TCD_SYNC_bm;
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
}

void initialize(void)
{
    ina266_init();
    balancer_timer_tcd_init();
    
    TCB0_CaptureCallbackRegister(tcb0_handler);
}