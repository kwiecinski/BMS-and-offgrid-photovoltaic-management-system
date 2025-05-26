#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "inits.h"
#include "interrupts.h"

#define PWM_24V_CMP_REGISTER                TCD0.CMPASET    // off=MAX_CMP_VALUE
#define PWM_12V_CMP_REGISTER                TCD0.CMPBSET    // off=0

#define PWM_MAX 4000
#define PWM_MIN 0
#define MAX_CELL_VOLTAGE_DIFFRENCE          10
#define DEAD_VOLTAGE_DIFFRENCE              2
#define MAX_CMP_VALUE                       4000    
#define MINIMUM_CELL_VOLTAGE                1270
#define MINIMUM_CELL_VOLTAGE_LOW            1250
#define MAX_CELL_VOLTAGE_ERROR_DIFFERENCE   300             //i.e 300 -> 3.00V
#define TIMEOUT                             5000
#define GND_VOLTAGE_DROP_BIAS_VOLTAGE       1246            //REFRENCE_VOLTAGE/2 but measured using multimeter

void measure_voltages(balancer_struct *ptr);
void set_pwm(balancer_struct *ptr);
int16_t calculate_gnd_voltage_drop(void);
uint16_t pid_step(PID *pid, int16_t measurement, int16_t setpoint);
void balancer_struct_init(balancer_struct *ptr);
void pid_init(PID *pid);


void balance_cells(balancer_struct *ptr, PID *pid)
{
    measure_voltages(ptr);
    int16_t cell_voltage_diff = ptr->voltage_batt_12V - ptr->voltage_batt_24V;     //iff cell diff negative then need to load 24V batt
    
    if(ptr->voltage_batt_12V >= MINIMUM_CELL_VOLTAGE && ptr->voltage_batt_24V >= MINIMUM_CELL_VOLTAGE)
    {
        if(cell_voltage_diff>0)
        {
            ptr->pwm_12V = pid_step(pid,  abs(cell_voltage_diff),  0);
         
        }else
        {
            ptr->pwm_24V = pid_step(pid,  abs(cell_voltage_diff),  0);
        }
        
    }else if(ptr->voltage_batt_12V >= MINIMUM_CELL_VOLTAGE )
    {
        ptr->pwm_12V = pid_step(pid,  ptr->voltage_batt_12V,   MINIMUM_CELL_VOLTAGE );
    
    }else if(ptr->voltage_batt_24V >= MINIMUM_CELL_VOLTAGE)
    {
         ptr->pwm_24V = pid_step(pid,  ptr->voltage_batt_24V,   MINIMUM_CELL_VOLTAGE );
         
    }else if(ptr->voltage_batt_12V < MINIMUM_CELL_VOLTAGE_LOW && ptr->voltage_batt_24V < MINIMUM_CELL_VOLTAGE_LOW)
    {
        ptr->pwm_12V=0;
        ptr->pwm_24V=0;
    }
    
       set_pwm(ptr);
}


void pid_init(PID *pid)
{
    pid->Kp = 10.0f;    // Proportional gain constant
    pid->Ki = 0.7f;     // Integral gain constant
    pid->Kd = 2.5f;     // Derivative gain constant
    pid->Kaw = 0.3f;    // Anti-windup gain constant
    pid->T_C = 1.0f;    // Time constant for derivative filtering
    pid->T = 0.05f;     // Time step
    pid->max = PWM_MAX;
    pid->min = PWM_MIN;
    pid->max_rate = 5000.0f;     // Max rate of change of the command
    pid->integral = 0;
    pid->err_prev = 0;
    pid->deriv_prev = 0;
    pid->command_sat_prev = 0;
    pid->command_prev = 0;
}

// G?ówna funkcja PID

uint16_t pid_step(PID *pid, int16_t measurement, int16_t setpoint)
{
    float err = (float) (measurement - setpoint); // jednostka: setne V


    float deriv_filt = (err - pid->err_prev + pid->T_C * pid->deriv_prev) / (pid->T + pid->T_C);
    pid->err_prev = err;
    pid->deriv_prev = deriv_filt;

    pid->integral += pid->Ki * err * pid->T + pid->Kaw * (pid->command_sat_prev - pid->command_prev) * pid->T;

    float command = pid->Kp * err + pid->integral + pid->Kd * deriv_filt;
    pid->command_prev = command;

    // Saturacja
    float command_sat = command;
    if (command_sat > pid->max)
    {
        command_sat = pid->max;
    }
    else if (command_sat < pid->min)
    {
        command_sat = pid->min;
    }

    // Rate limiter
    float delta = pid->max_rate * pid->T;
    if (command_sat > pid->command_sat_prev + delta)
    {
        command_sat = pid->command_sat_prev + delta;
    }
    else if (command_sat < pid->command_sat_prev - delta)
    {
        command_sat = pid->command_sat_prev - delta;
    }

    pid->command_sat_prev = command_sat;

    return (uint16_t) command_sat;

}

void balancer_struct_init(balancer_struct *ptr)
{
    ptr->voltage_bus = 0;
    ptr->voltage_batt_12V = 0;
    ptr->voltage_batt_24V = 0;
    ptr->pwm_12V = 0;
    ptr->pwm_24V = 0;
    ptr->minimum_cell_voltage = MINIMUM_CELL_VOLTAGE;
    ptr->voltage_drop = 0;
}


int16_t calculate_gnd_voltage_drop(void)
{
    int16_t voltage_drop = Get_ADC_Voltage(ADC_CHANNEL_GND_VOLTAGE_DROP);

    if (voltage_drop > GND_VOLTAGE_DROP_BIAS_VOLTAGE) //discharging
    {
        voltage_drop = voltage_drop - GND_VOLTAGE_DROP_BIAS_VOLTAGE;
    }
    else //charging
    {
        voltage_drop = GND_VOLTAGE_DROP_BIAS_VOLTAGE - voltage_drop;
    }

    return voltage_drop;
}


void measure_voltages(balancer_struct *ptr)
{
    //voltages are in format i.e: 1253 -> 12.53V, 546 -> 5,46V
    ptr->voltage_bus = AutoFox_INA226_GetBusVoltage_V(&ina226);
    ptr->voltage_batt_12V = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 10; //devide by 10 to get desired resolution, the same as voltage_bus
    ptr->voltage_batt_24V =  ptr->voltage_bus -  ptr->voltage_batt_12V;
    ptr->voltage_drop = calculate_gnd_voltage_drop();
}


void set_pwm(balancer_struct *ptr)
{
    if (ptr->pwm_12V > MAX_CMP_VALUE)
    {
        ptr->pwm_12V = MAX_CMP_VALUE;
    }

    if (ptr->pwm_24V > MAX_CMP_VALUE)
    {
        ptr->pwm_24V = MAX_CMP_VALUE;
    }

    while (!(TCD0.STATUS & TCD_CMDRDY_bm)); // CMDRDY == 1

    PWM_24V_CMP_REGISTER = MAX_CMP_VALUE - ptr->pwm_24V;
    PWM_12V_CMP_REGISTER = ptr->pwm_12V;

    TCD0.CTRLE |= TCD_SYNC_bm;
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
}


/*
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
*/