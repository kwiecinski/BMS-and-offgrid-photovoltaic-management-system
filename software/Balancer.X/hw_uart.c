#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "hw_uart.h"

#define BaudRate    9600
#define SPBRG_Reg_Val   (_XTAL_FREQ/BaudRate)/64-1

void UART_Init(void)
{
    RCSTAbits.SPEN=1;       //SPEN: Serial Port Enable bit
    RCSTAbits.CREN=1;       //Continuous Receive Enable bit
    TXSTAbits.SYNC=0;       //EUSART Mode Select bit: 0 - Asynchronous
    TXSTAbits.TXEN=1;
    SPBRG=SPBRG_Reg_Val;    //EUSART Baud Rate Generator Register, Low Byte   
}

void SendUART(char data) 
{
  while(!TRMT);     // check buffer
  TXREG = data;     // send data
}

/*

unsigned char DigitToString(unsigned char digit)
{
    unsigned char i;

    for(i=0;i<10;i++)
    {
        if(digit==i)
		{
			return('0'+i);
		}
    }      
    
    return 0;
}



void SendArrayUART(unsigned char *data, unsigned char size)
{
    unsigned char i;
    
    for(i=0;i<size;i++)
    {
        SendUART(*(data+i));
    }
}


void SendDigitUART(unsigned int data)
{
    if(data<=0xFF)
    {
        SendUART(DigitToString(data%1000/100));
        SendUART(DigitToString(data%100/10));
        SendUART(DigitToString(data%10));
       
        
    }else if(data>0xFF)
    {
        SendUART(DigitToString(data%100000/10000)); 
        SendUART(DigitToString(data%10000/1000)); 
        SendUART(DigitToString(data%1000/100));
        SendUART(DigitToString(data%100/10));
        SendUART(DigitToString(data%10));
   
    }
    SendUART('\n');
    SendUART('\r');
}
*/