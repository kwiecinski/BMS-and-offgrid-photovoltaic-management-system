#include <xc.h>
#include <util/atomic.h>


volatile uint32_t millis_counter = 0;
volatile uint16_t balancer_12V_timer = 0;
volatile uint16_t balancer_24V_timer = 0;

void tcb0_handler(void)
{
    millis_counter++;

    if (balancer_12V_timer > 0)
    {
        balancer_12V_timer--;
    }

    if (balancer_24V_timer > 0)
    {
        balancer_24V_timer--;
    }
}

uint32_t millis(void)
{
    uint32_t ms;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        ms = millis_counter;
    }
    return ms;
}
