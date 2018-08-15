/*************************************************************************
*
* Lab2bx
* Hardware: LaunchPad (MSP430G2553)
* File: lab2bx.c
* Objective: To blink green LED on the LaunchPad
*
*************************************************************************/

#include <msp430g2553.h>

void main (void)
{
 	WDTCTL = WDTPW | WDTHOLD;      	//Stop Watchdog Timer

	P1DIR |= 0x41;                 	//Configure LED1 and LED2 ports as Output

	while(1)			// Infinite Loop
	{
	  P1OUT = 0x40; 		// LED on
	  _delay_cycles(1000);
	  P1OUT = 0x00; 		// LED off
	  _delay_cycles(500000);
	}
}
