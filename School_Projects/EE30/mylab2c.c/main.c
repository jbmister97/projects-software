/*************************************************************************
* Lab2c
* Hardware: LaunchPad (MSP430G2553)
* File: lab2c.c
* Objective: To blink the Red LED on the LaunchPad.
*
*************************************************************************/

#include <msp430g2553.h>

	long int i;

void main (void)
{
	WDTCTL = WDTPW | WDTHOLD;      		// Stop Watchdog Timer

    P1DIR |= 0x01;                 		// Configure Red LED port as output
	P1OUT = 0x01; 				// Turn Red LED on

	while(1)				// Infinite loop

	{
	      	i = 5000;         	        // Delay

		while(i > 0) { i--;}

		P1OUT ^= 0x01;               	// Toggle LED

	}
}
