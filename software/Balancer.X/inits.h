/* 
 * 
 * 
 *
 * 
 */

#ifndef INITS_H
#define	INITS_H

void Global_Init(void);

#define PWM_DISCHARGE_BATTERY  PORTCbits.RC0
#define PWM_CHARGE_BATTERY     PORTCbits.RC1

#define BALANCE_BATT_12V_ON   PORTBbits.RB4=0
#define BALANCE_BATT_12V_OFF  PORTBbits.RB4=1

#define BALANCE_BATT_24V_ON   PORTBbits.RB5=0
#define BALANCE_BATT_24V_OFF  PORTBbits.RB5=1


#define STATUS_LED_D19_ON       PORTBbits.RB2=1
#define STATUS_LED_D19_OFF      PORTBbits.RB2=0

#define STATUS_LED_D18_ON       PORTBbits.RB3=1
#define STATUS_LED_D18_OFF      PORTBbits.RB3=0

#define STATUS_LED_D21_ON       PORTBbits.RB6=1
#define STATUS_LED_D21_OFF      PORTBbits.RB6=0

#define STATUS_LED_D20_ON       PORTBbits.RB7=1
#define STATUS_LED_D20_OFF      PORTBbits.RB7=0

#define STATUS_LED_D23_ON       PORTCbits.RC0=1
#define STATUS_LED_D23_OFF      PORTCbits.RC0=0


#define STATUS_LED_D5_ON       PORTAbits.RA6=1
#define STATUS_LED_D5_OFF      PORTAbits.RA6=0

#endif	/* INITS_H */

