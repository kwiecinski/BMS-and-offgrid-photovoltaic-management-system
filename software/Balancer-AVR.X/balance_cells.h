
#ifndef BALANCE_CELLS
#define	BALANCE_CELLS

//#include <xc.h> // include processor files - each processor file is guarded.  

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float Kaw;
    float T_C;
    float T;
    float max;
    float min;
    float max_rate;
    float integral;
    float err_prev;
    float deriv_prev;
    float command_sat_prev;
    float command_prev;
}PID;

typedef struct
{
    uint16_t voltage_bus,voltage_batt_12V,voltage_batt_24V,
              pwm_12V, pwm_24V, minimum_cell_voltage;
    int16_t voltage_drop;
    
            
}balancer_struct;

void balancer_struct_init(balancer_struct *ptr);
void balance_cells(balancer_struct *ptr, PID *pid);
void pid_init(PID *pid);

extern volatile int16_t balancer_12V_timer, balancer_24V_timer;

#endif

