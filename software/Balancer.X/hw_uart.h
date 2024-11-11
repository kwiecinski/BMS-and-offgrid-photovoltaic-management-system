/* 
 * 
 * 
 *
 * 
 */

#ifndef HW_UART_H
#define	HW_UART_H

void UART_Init(void);
void SendUART(char data);
void SendArrayUART(unsigned char *data, unsigned char size);
void SendDigitUART(unsigned int data);
unsigned char DigitToString(unsigned char digit);
#endif	/* HW_URAT_H */