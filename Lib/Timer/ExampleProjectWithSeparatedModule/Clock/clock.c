#include "msp430.h"
#include "clock.h"
void config_clock(void)
{
    BCSCTL1 = CALBC1_1MHZ;          // set range
    DCOCTL = CALDCO_1MHZ;
}
