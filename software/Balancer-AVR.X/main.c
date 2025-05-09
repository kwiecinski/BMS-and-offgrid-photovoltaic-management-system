#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "inits.h"

void TCB_ISR_handler(void);

AutoFox_INA226 ina226;

int main(void)
{
    SYSTEM_Initialize();
    initialize();

    //Printf init -------------------------------------------------------------
    stdout = stdout_ptr;
    // ------------------------------------------------------------------------

    while (1)
    {
     
        balance_cells();
        
        
         //DELAY_milliseconds(1);
    }
}

static int16_t balancer_timer=0;

void TCB_ISR_handler(void)
{
    balancer_12V_timer--;
    if(balancer_12V_timer < 0)
    {
        balancer_12V_timer = 0;
    }

    balancer_24V_timer--;
    if(balancer_24V_timer < 0)
    {
        balancer_24V_timer = 0;
    }
    TCB0.INTFLAGS = TCB_CAPT_bm; // Clear interrupt flag
}



