/******************************************************************************
 *
 * www.payitforward.edu.vn
 *
 ******************************************************************************/

/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : TIMER.H
 *    Description  : This header file includes definitions and prototypes of
 *          API functions that support you to use TIMER
 *
 *  Tool           : CCS 5.1
 *  Chip           : MSP430G2xx3 (MCU that haves USCI_A0 module)
 *  History        : 17/01/2019
 *  Version        : 1.2
 *
 *  Author         : QThai16 - PIFer
 *  Notes          :
 *      To apply these functions, you must include this header file and add
 *      the TIMER.c file to your project.
 *
 *      You should consult the Launch Pad schematic in Launch Pad User's Guide
 *      for easier connecting.
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/

#include <msp430.h>

void timer_init(void);

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;
	timer_init();
	_BIS_SR(GIE);
	while(1)
	{

	}
}

void timer_init(void)
{
	/*****************INITIATE TIMER A0*****************/
	TA0CCR0 = 1150;
    TA0CCR1 = 500;
    TA0CCR2 = 500;
    TA0CTL |= TASSEL_2 + MC_1;
    TA0CCTL1 |= OUTMOD_7;

    P1SEL|= BIT6;
    P1SEL2 &=~ BIT6;
    P1DIR |= BIT6; //P1.6 PWM output
    /*****************INITIATE TIMER A1*****************/
	TA1CCR0 = 5000;
    TA1CCR1 = 2500;
    TA1CCR2 = 2500;
    TA1CTL |= TASSEL_2 + MC_1;
    TA1CCTL1 |= OUTMOD_7;
    TA1CCTL2 |= OUTMOD_7;

	P2SEL|= (BIT1 + BIT4);
	P2SEL2 &=~ (BIT1 + BIT4);
	P2DIR |= (BIT1 + BIT4); ////P2.1 and P2.4 PWM Output

//**	Neu muon dung ngat CCR0, CCR1, CCR2 va Overflow Interrupt, bo commend dong nay va commend cac dong tren**//
//
//		TA0CTL |= TASSEL_2 + MC_1 + TAIE + TAIFG; //Clk 1Mhz, up mode , interrupt enable, interrupt flag
//      TA1CTL |= TASSEL_2 + MC_1 + TAIE + TAIFG;
//      TA1CCTL1 |= CCIE+CCIFG;
//      TA1CCTL2 |= CCIE+CCIFG;
//      TA0CCTL1 |= CCIE+CCIFG;
//      TA0CCTL2 |= CCIE+CCIFG;

/* -TASSEL_x : select clock source
			0: TACLK
			1: ACLK
			2: SMCLK
			3: INCLK
   -ID_x : input divider
			0: /1
			1: /2
			2: /4
			3: /8
   -MC_x : mode control
			0: stop mode: timer is halted
			1: up mode: 0 -> TACCR0
			2: continuous mode: 0 -> 0FFFFh
			3: up/down mode: 0 -> TACCR0 -> 0
   -TAIE : timer interupt enable
   -TAIFG : interupt pending
   */
}

/****************************************************************************
* TIMER A0 INTERRUPT SERVICE ROUTINE
******************************************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void timer0(void)
{
	switch (TA0IV)
	{
	case 2: //CCR1 overflow interupt
	{
//			do something here
			break;
	}
	case 4: //CCR2 overflow interupt
	{
//			do something here
			break;
	}
	case 10: //timer overflow
	{
//			do something here
		break;
	}
	}
}

#pragma vector=TIMER0_A0_VECTOR 	//ISR CCR0
__interrupt void timer0ccr0(void)
{
//			do something here
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer1(void)
{
	switch (TA1IV)
	{
	case 2: //CCR1 overflow interupt
	{
//			do something here
			break;
	}
	case 4: //CCR2 overflow interupt
	{
//			do something here
			break;
	}
	case 10: //timer overflow
	{
//			do something here
		break;
	}
	}
}

#pragma vector=TIMER1_A0_VECTOR 	//ISR CCR0
__interrupt void timer1ccr0(void)
{
//			do something here
}
