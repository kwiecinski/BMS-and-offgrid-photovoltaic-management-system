#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
#include "balance_cells.h"
#include "inits.h"


#define MAX_CELL_VOLTAGE_DIFFRENCE          10
#define DEAD_VOLTAGE_DIFFRENCE              2
#define MAX_CMP_VALUE                       4000    
#define PWM_24V_CMP_REGISTER                TCD0.CMPASET    // off=MAX_CMP_VALUE
#define PWM_12V_CMP_REGISTER                TCD0.CMPBSET    // off=0
#define KP_12V                              50
#define KP_24V                              50
#define MINIMUM_CELL_VOLTAGE                1380 
#define MAX_CELL_VOLTAGE_ERROR_DIFFERENCE   300             //i.e 300 -> 3.00V
#define PWM_STEP                            10
#define TIMEOUT                             5000
#define GND_VOLTAGE_DROP_BIAS_VOLTAGE       1246            //REFRENCE_VOLTAGE/2 but measured using multimeter


void set_pwm(uint16_t set_12V_batt_pwm, uint16_t set_24V_batt_pwm);
int16_t calculate_gnd_voltage_drop(void);

void balance_cells(void)
{
    //voltages are in format i.e: 1253 -> 12.53V, 546 -> 5,46V

    static uint16_t current_pwm = 0;
    // DELAY_milliseconds(200);
    // set_pwm(0, 0);
    //DELAY_milliseconds(10);
    uint16_t voltage_bus = AutoFox_INA226_GetBusVoltage_V(&ina226);
    uint16_t voltage_batt_12V = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 10; //devide by 10 to get desired resolution, the same as voltage_bus
    uint16_t voltage_batt_24V = voltage_bus - voltage_batt_12V;

      uint16_t voltage_drop = Get_ADC_Voltage(ADC_CHANNEL_GND_VOLTAGE_DROP);
    
    printf("24V:%u mV \r\n", voltage_batt_24V);
    printf("12V:%u mV \r\n", voltage_batt_12V);
    printf("GND_V_DROP:%d mV \r\n", GND_VOLTAGE_DROP_BIAS_VOLTAGE-voltage_drop);
    printf("BUS INA:%u   \r\n\r\n", voltage_bus);

    int16_t cell_voltage_diffrence = (int16_t) voltage_batt_12V - (int16_t) voltage_batt_24V; //calculating voltage difference between batteries

    uint16_t target_pwm = 0;


    if ((voltage_batt_12V >= MINIMUM_CELL_VOLTAGE && voltage_batt_24V >= MINIMUM_CELL_VOLTAGE))
    {
        if (cell_voltage_diffrence < 0)
        {
            target_pwm = KP_24V * abs(cell_voltage_diffrence);
        }
        else
        {
            target_pwm = KP_12V * abs(cell_voltage_diffrence);
        }
    }
    else
    {
        if ((voltage_batt_12V >= MINIMUM_CELL_VOLTAGE && voltage_batt_24V < MINIMUM_CELL_VOLTAGE))
        {
            target_pwm = KP_12V * (MINIMUM_CELL_VOLTAGE - voltage_batt_24V);

        }
        else if (voltage_batt_12V < MINIMUM_CELL_VOLTAGE && voltage_batt_24V >= MINIMUM_CELL_VOLTAGE)
        {
            target_pwm = KP_24V * (MINIMUM_CELL_VOLTAGE - voltage_batt_12V);
        }

    }


    printf("cell_voltage_diffrence: %i \n\r", abs(cell_voltage_diffrence));
    printf("current_pwm: %u \n\r", current_pwm);

    if (target_pwm > MAX_CMP_VALUE)
    {
        target_pwm = MAX_CMP_VALUE;
    }

    if (target_pwm > current_pwm)
    {
        current_pwm += PWM_STEP;
        if (current_pwm > target_pwm)
        {
            current_pwm = target_pwm;
        }
    }
    else
    {
        current_pwm -= PWM_STEP;
        if (current_pwm < target_pwm)
        {
            current_pwm = target_pwm;
        }
    }

    printf("timer12, timer24: %u, %u \n\r", balancer_12V_timer, balancer_24V_timer);

    if (abs(cell_voltage_diffrence) < MAX_CELL_VOLTAGE_ERROR_DIFFERENCE)
    {
        if (voltage_batt_12V > (MINIMUM_CELL_VOLTAGE - 20) || voltage_batt_24V > (MINIMUM_CELL_VOLTAGE - 20))
        {
            if ((cell_voltage_diffrence < -DEAD_VOLTAGE_DIFFRENCE) && balancer_24V_timer == 0) //if true then voltage for battery 24V has higher voltage, and we need to load this cell
            {
                balancer_12V_timer = TIMEOUT;
                set_pwm(0, current_pwm);
                printf("load 24V \n\r");

            }
            else if ((cell_voltage_diffrence > DEAD_VOLTAGE_DIFFRENCE) && balancer_12V_timer == 0)
            {
                balancer_24V_timer = TIMEOUT;
                set_pwm(current_pwm, 0);
                printf("load 12V \n\r");
            }
            else
            {
                set_pwm(0, 0);
                printf("no balancing - dead zone\n\r");
            }
        }
        else
        {
            set_pwm(0, 0);
            //current_pwm = 0;
            printf("no balancing - minimum cell voltage not true\n\r");
        }
    }
    else
    {
        set_pwm(0, 0);
        printf("no balancing - too much cell voltage diffrence\n\r");
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


    printf("set_24V_batt_pwm: %u \n\r", set_24V_batt_pwm);
    printf("set_12V_batt_pwm: %u \n\r", set_12V_batt_pwm);
    PWM_24V_CMP_REGISTER = MAX_CMP_VALUE - set_24V_batt_pwm;
    PWM_12V_CMP_REGISTER = set_12V_batt_pwm;

    TCD0.CTRLE |= TCD_SYNC_bm;
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
}