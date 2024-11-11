/* 
 * 
 * 
 *
 * 
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#define FALLING_EDGE    CCP2CONbits.CCP2M=0b0100
#define RISING_EDGE     CCP2CONbits.CCP2M=0b0101
#define FALL_FLAG       0
#define RISE_FLAG       1
#define COMPARE_SET     CCP1CONbits.CCP1M=0b1000        //Compare mode, set output on match (CCP1IF bit is set)
#define COMPARE_CLEAR   CCP1CONbits.CCP1M=0b1001 

void Interrupt_Init(void);


#endif	/* INTERRUPTS_H */

