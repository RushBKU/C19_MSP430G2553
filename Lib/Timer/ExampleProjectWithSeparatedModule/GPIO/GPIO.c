#include "GPIO.h"
#include "msp430.h"

void GPIO_init(void)
{
    P1SEL &=~ (BIT0+BIT6);
    P1SEL2 &=~ (BIT0+BIT6);
    P1DIR |= (BIT0 + BIT6);
    P1OUT |= (BIT0+BIT6);
}
void GPIO_toggle(void)
{
    P1OUT |= (BIT0 + BIT6);
    __delay_cycles(1000000);
    P1OUT &= ~(BIT0 + BIT6);
    __delay_cycles(1000000);
}
