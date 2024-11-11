///////////////////////////////////////////////////////////////////////////////
//
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "sw_uart.h"
#include "hw_uart.h"

#define		BAUD_RATE_UART  	1200
#define     TX_HIGH            PORTAbits.RA4=1
#define     TX_LOW             PORTAbits.RA4=0
#define     BIT_TIME_US      (1000000 / BAUD_RATE_UART) 


void SendUART_debug(unsigned char data) 
{
    INTCONbits.GIE=0;
	TX_LOW;
	__delay_us(BIT_TIME_US);

	for(unsigned char i=0;i<8;i++)
	{
		if(data & (1 << i))
		{
			TX_HIGH;
		}else
		{
			TX_LOW;
		}
		__delay_us(BIT_TIME_US);
	}

	TX_HIGH;
	__delay_us(BIT_TIME_US);
    INTCONbits.GIE=1;
}


void SendArrayUART_debug(unsigned char *data, unsigned char size)
{
    unsigned char i;
    
    for(i=0;i<size;i++)
    {
        SendUART_debug(*(data+i));
    }
    
}

void SendDigitUART_debug(unsigned int data)
{
    if(data<=0xFF)
    {
        SendUART_debug(DigitToString(data%1000/100));
        SendUART_debug(DigitToString(data%100/10));
        SendUART_debug(DigitToString(data%10));
       
        
    }else if((data>0x00FF) && (data<=0xFFFF))
    {
        SendUART_debug(DigitToString(data%100000/10000)); 
        SendUART_debug(DigitToString(data%10000/1000)); 
        SendUART_debug(DigitToString(data%1000/100));
        SendUART_debug(DigitToString(data%100/10));
        SendUART_debug(DigitToString(data%10));
   
    }
}


void itoa(int32_t value, char *str, int numeral_base)
{
    int32_t i = 0;
    int32_t isNegative = 0;

    // Je?li warto?? jest ujemna, oznaczamy to i zmieniamy warto?? na dodatni?
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Dzielimy liczb? przez baz? i zapisujemy reszty (cyfry)
    do {
        str[i++] = (value % numeral_base) + '0';  // Dodajemy cyfr? (zamieniaj?c na znak ASCII)
        value = value / numeral_base;
    } while (value != 0);

    // Dodajemy znak minus, je?li liczba by?a ujemna
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';  // Ko?czymy ci?g znaków

    // Odwracamy ci?g znaków, poniewa? numeryczne cyfry by?y dodawane od ko?ca
    int32_t start = 0;
    int32_t end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void SendInt32ToUART(int32_t value)
{
    char buffer[12];  // Bufer do przechowania tekstowej reprezentacji liczby, max 11 znaków + terminator

    // Konwersja liczby ca?kowitej na tekst (ASCII)
    itoa(value, buffer, 10);  // Funkcja itoa() konwertuje liczb? ca?kowit? na ci?g znaków w systemie dziesi?tnym

    // Wysy?anie ka?dego znaku przez UART
    for (int i = 0; buffer[i] != '\0'; i++) {
        SendUART_debug(buffer[i]);  // Wysy?anie pojedynczego znaku
    }
}