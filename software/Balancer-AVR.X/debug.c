#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "main.h"
#include "uart_remap.h"
#include "balance_cells.h"
#include "interrupts.h"

void printf_debug(balancer_struct *ptr, PID *pid)
{
    printf("\x1b[2J\x1b[H");        //clear terminal
    printf("24V: %u mV \r\n", ptr->voltage_batt_24V);
    printf("12V: %u mV \r\n", ptr->voltage_batt_12V);
    printf("GND V DROP: %d mV \r\n", ptr->voltage_drop);
    printf("Cell V DIFF: %d \n\r", abs(ptr->voltage_batt_24V - ptr->voltage_batt_12V));
    printf("PWM 12V: %u \n\r", ptr->pwm_12V);
    printf("PWM 24V: %u \n\r", ptr->pwm_24V);
    
    printf("PID balancer data: \n\r");
    printf("PWM 24V: %u \n\r", ptr->pwm_24V);
    printf("PID Integral: %f \n\r", pid->integral);
    printf("PID Derivative: %f \n\r", pid->deriv_prev);
    printf("PID Command: %f \n\r", pid->command_prev);
}