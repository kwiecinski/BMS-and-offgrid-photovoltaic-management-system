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
void TCB_ISRc_handler(void);

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
        uint16_t voltage_bus_24V, voltage_batt_12V_high, voltage_batt_12V_low;

        voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
        voltage_batt_12V_low = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 10;
        voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;

        printf("24V:%u mV \r\n", voltage_batt_12V_high);
        printf("12V:%u mV \r\n", voltage_batt_12V_low);
        printf("BUS INA:%u   \r\n\r\n", voltage_bus_24V);

      //  DELAY_milliseconds(1);
        balance_cells();
        printf("TCD0.CMPASET (24V): %d \n\r", TCD0.CMPASET);
        printf("TCD0.CMPBSET (12V): %d \n\r", TCD0.CMPBSET);
    }
}

void TCB_ISR_handler(void)
{
}



