/*************************************************************************
*
* Lab2a
* Hardware: LaunchPad (MSP430G2553)
* File: lab2a.c
* Objective: To blink LED1 on the LaunchPad
*
*************************************************************************/

#include <msp430g2553.h>
 int AGE = 23;

void main (void)
{

	P1DIR |= 0x41;                 	//Configure LEDs ports as output
	P1OUT = 0;			//Turn LEDs off

	if ((AGE < 18) || (AGE > 65))
	{
	  P1OUT = 0x01; 		// Red LED on, Green LED off
	}
	else
	{
	  P1OUT = 0x40; 		// Red LED off, Green LED on
	}
}
