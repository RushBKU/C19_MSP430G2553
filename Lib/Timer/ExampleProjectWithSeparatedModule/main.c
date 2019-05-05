#include <msp430.h> 
#include "Clock/clock.h"
#include "GPIO/GPIO.h"
/**
 * main.c
 */
int i=0;
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	config_clock();
	GPIO_init();
	while(1)
	{
	    GPIO_toggle();
	    i++;
	}
	return 1;
}
