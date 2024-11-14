/* 
 * 
 * 
 *
 * 
 */
#include <xc.h>
#include "main.h"

///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

void I2C_Init(void)
{
    //Configures the SDA and SCL pins as the source of the serial port pins
    SSPCONbits.SSPEN=1;
    SSPCONbits.SSPM=0b1000;
    SSPADD=19;    //see explanation below
    /*
    * SSPADD (Synchronous Serial Port Address) Register:
    *
    * The `SSPADD` register in the PIC16F886 is used to set the clock frequency for I2C communication in Master mode.
    * It determines the baud rate for the I2C bus by dividing the system clock (`F_osc`) by a factor calculated from the value
    * stored in `SSPADD`. The formula to calculate the I2C clock frequency is:
    *
    * I2C Clock Frequency (SCL) = F_osc / (4 * (SSPADD + 1))
    *
    * Where:
    * - F_osc is the system oscillator frequency (e.g., 8 MHz).
    * - SSPADD is the 8-bit register value that defines the division factor.
    *
    * For example, with an 8 MHz system clock and wanting to set the I2C clock to 100 kHz, the `SSPADD` value can be calculated as:
    *
    * SSPADD = (F_osc / (4 * I2C Clock Frequency)) - 1
    * SSPADD = (8,000,000 / (4 * 100,000)) - 1 = 19
    *
    * In this case, setting `SSPADD` to 19 would result in an I2C clock frequency of approximately 100 kHz.
    *
    * Note that in Master mode, you need to configure `SSPADD` properly to ensure the correct I2C bus speed.
    * In Slave mode, the `SSPADD` value does not directly affect I2C clock speed but can be used in SPI mode settings if configured.
    */
    

    SSPCON2=0;
    //SSPSTAT=0;
    SSPSTATbits.SMP=1; //1 = Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)
}
///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

void I2C_Master_Wait(void)
{
    while (SSPCON2bits.RCEN || SSPCON2bits.PEN || SSPCON2bits.RSEN || 
          SSPCON2bits.SEN || SSPCON2bits.ACKEN || SSPSTATbits.R_nW)
    {
    }; 
}

///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

void I2C_Master_Start(void)
{
    I2C_Master_Wait();  
    SSPCON2bits.SEN=1;
}

///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

void I2C_Master_Stop(void)
{
    I2C_Master_Wait();
    SSPCON2bits.PEN=1;
}

///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

void I2C_Master_Write(unsigned data)
{   
    I2C_Master_Wait();
    SSPBUF=data;
}

///////////////////////////////////////////////////////////////////////////////
///
/// 
/// 
/// 
///
///////////////////////////////////////////////////////////////////////////////

unsigned char I2C_Master_Read(unsigned char ack)
{
    unsigned short data;
    I2C_Master_Wait();
    RCEN=1;                 //Receive Enable bit 
    I2C_Master_Wait();
    data=SSPBUF;            //Read data from SSPBUF
    I2C_Master_Wait();
    ACKDT=(ack)?0:1;        //check if ack bit received  
    ACKEN=1;         
    return data;
}