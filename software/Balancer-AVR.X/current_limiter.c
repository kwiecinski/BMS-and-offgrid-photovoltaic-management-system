#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "current_limiter.h"
#include "inits.h"
#include "interrupts.h"


void current_limiter(void)
{
    TCA0.SINGLE.PER = 479;
    TCA0.SINGLE.CMP0 = 20;
    TCA0.SINGLE.CMP1 = 100;

}