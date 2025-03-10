/*
 * File:   uart_remap.c
 * Author: RaD
 *
 * Created on November 8, 2022, 12:36 PM
 */


#include <stdio.h>
#include <avr/io.h>
#include "mcc_generated_files/system/system.h"
#include "uart_remap.h"



static int uart_putchar(char c, FILE * stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE *stdout_ptr =  &mystdout;

void UART_TX(uint8_t txData)
{    
    while(!(DEBUG_UARAT_IsTxReady()));
    DEBUG_UARAT_Write(txData);                      // Write the data byte to the UART.
}

static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n')
    {
        uart_putchar('\r', stream);
    }
    UART_TX(c);
    return 0;
}
