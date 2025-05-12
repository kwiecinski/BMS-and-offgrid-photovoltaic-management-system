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
/*
        if (test > 1000)
        {
            printf("test ok \n\r");
            test = 0;
        }
  */
        //DELAY_milliseconds(1);
    }
}




