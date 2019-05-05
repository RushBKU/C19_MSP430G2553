#include <msp430.h>
#include "UART/UART.h"

#include <stdio.h>
#include <stdint.h>

#define SPEED_OF_SOUND  34000          // cm/s
#define SYS_CLOCK       1000000
#define TRIGGER         BIT1            //Port 2
#define ECHO            BIT0            //Port 2
#define PIN_PWM_OUT     BIT6            //Port 1


unsigned int t1, t2, distance, first_pulse;


void PWM_init(void)
{
    // Configure timer 0 outmode for PWM module
    TA0CCR0 = 512;
    TA0CCR2 = 150;
    TA0CCR1 = TA1CCR2 + 20;
    TA0CTL = TASSEL_2 + MC_3 ;                 // SMCLK, Up mode
    TA0CCTL1 = OUTMOD_2; //+ CCIE;             // falling edge & raising edge, capture mode, capture/compare
    TA0CCTL2 = OUTMOD_6;
}

void PWM_update(uint16_t duty)
{
    TA0CCR1 = duty + 20;
    TA0CCR2 = duty;
}

void ultrasonic_init(void){
   // Configure timer 1 capture mode for ultrasonic module
   TA1CTL = TASSEL_2 + MC_2 ;                       // continuos mode, 0 --> FFFF
   TA1CCTL0 = CM_3 + CAP + CCIS_0 + SCS+ CCIE;      // falling edge & raising edge, capture mode, capture/compare interrupt enable
   TA1CCTL0 &= ~ CCIFG;
}

void GPIO_init(void)
{
    //Configure ultrasonic
    P2DIR |= TRIGGER;      // trigger ouput
    P2SEL |= ECHO;         //connect P2.0 (echo) to CCI0A (capture/compare input )

    //Configure pwm output
    P1DIR |= PIN_PWM_OUT;
    P1OUT &= ~PIN_PWM_OUT;
    P1SEL |= PIN_PWM_OUT;
    P1SEL2 &= ~PIN_PWM_OUT;
}

void clock_init(void)
{
    //Configure clock
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;          // set range
    DCOCTL = CALDCO_1MHZ;           // set DCO step + moudulation
}


void main(void)
 {
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer

    clock_init();
    GPIO_init();
    ultrasonic_init();
    uart_init();
    PWM_init();
    _BIS_SR(GIE);          //global interrupt


    while(1)
    {
        // Get distance
        P2OUT |= TRIGGER;       // Trigger measure time
        __delay_cycles(20);
        P2OUT &= ~TRIGGER;
        __delay_cycles(10000);

        //Control LED
        int duty = distance*4;  // Normalize duty value
        if(duty>500)
        {
            duty = 500;
        }
        PWM_update((uint16_t)duty);

        // UART
        char buffer[50];
        sprintf(buffer, "Distance: %d \n", distance);
        uart_puts(buffer);
    }


}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer_1_interrupt(void){

   if (P2IN & BIT0 == 1 )      //  if rising edge at echo (P2.0)
      t1 = TA1CCR0;
   else
   {                  // if falling edge at echo (P2.0)
      t2 = TA1CCR0;
      if (t2 > t1)
      {
         distance = SPEED_OF_SOUND*(t2-t1)/2/SYS_CLOCK;
      }
   }

   TA1CCTL0 &= ~ CCIFG;
}
