/*****************************************************************************
 *             *SPI CODE TEST*
 * Connect Vseg and SPI HW jumper
 * Make sure <LED7SEG> <74HC595> install correctly
*/
#include <msp430.h>
#include <Basic_Config/Basic_config.h>
#include <SPI/SPI.h>
#include <stdint.h>

// define 7segs
#define SEG1_BIT BIT5
#define SEG2_BIT BIT7
#define SEG3_BIT BIT6
#define SEG4_BIT BIT0
#define SEG1_PORT P2OUT
#define SEG2_PORT P2OUT
#define SEG3_PORT P2OUT
#define SEG4_PORT P1OUT

#define LATCH BIT5


unsigned char  led7s[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void Config_Led7Seg(void);

int  main (void)
{
    Config_stop_WDT();	// stop watchdog timer
	Config_Clocks();
	Config_SPI_A();
    Config_Led7Seg();

    SEG1_PORT  &=~ SEG1_BIT;
    while(1)
    {
        Send_byte_A(led7s[9],10);
        P1OUT &=~ LATCH;
        P1OUT |= LATCH;
    __delay_cycles(10000);
    }
    
        return 0;
}


void Config_Led7Seg(void){
    
    P1DIR   |= (SEG4_BIT);
    P2DIR   |= (SEG1_BIT+SEG2_BIT+SEG3_BIT);
    P1DIR   |=SEG4_BIT;
    P2DIR   |=(SEG1_BIT+SEG2_BIT+SEG3_BIT);
    P2SEL   &= ~(BIT6+BIT7);
    P2OUT   |=( SEG1_BIT+SEG2_BIT+SEG3_BIT);
    P1OUT   |=SEG4_BIT;
}