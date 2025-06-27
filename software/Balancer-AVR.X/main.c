#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "main.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "inits.h"
#include "temp_regulator.h"
#include "interrupts.h"
#include "debug.h"
#include "current_limiter.h"

AutoFox_INA226 ina226;

int main(void)
{
    SYSTEM_Initialize();
    initialize();
    
    balancer_struct balancer;
    balancer_struct_init(&balancer);
    
    PID balancer_pid;
    pid_init(&balancer_pid);
     
     
    //Printf init -------------------------------------------------------------
    stdout = stdout_ptr;
    // ------------------------------------------------------------------------

    uint32_t last_balance_time = 0, last_printf_time = 0;
    current_limiter();
    while (1)
    {
        uint32_t now = millis();
        
        if ((now - last_balance_time) >= 50)
        {
            last_balance_time = now;
           //balance_cells(&balancer, &balancer_pid);
          
        }
        
        if ((now - last_printf_time) >= 1000)
        {
            last_printf_time = now;
            printf_debug(&balancer, &balancer_pid);
        }
        
    }
}
