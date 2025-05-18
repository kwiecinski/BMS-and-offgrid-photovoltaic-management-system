
#ifndef BALANCE_CELLS
#define	BALANCE_CELLS

//#include <xc.h> // include processor files - each processor file is guarded.  

void balance_cells(void);
extern volatile int16_t balancer_12V_timer, balancer_24V_timer;

#define INCREASE 1
#define DECREASE 0

#endif

