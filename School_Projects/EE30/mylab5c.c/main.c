/******************************************************************************
* Lab 5
* Hardware: LaunchPad (MSP430G2553)
* File: lab5c.c
* Objective: To blink Green and Red LEDs on the LaunchPad using Function calls
* and passing values by 'call by address' method.
*******************************************************************************/
#include <msp430g2553.h>

int greenledblink(int *);
int redledblink(int *);
int toggleblink(int *);
int green, red, toggle;

int greenledblink(int *greencounts)
	{
	    int a, iterations = 0;
	    while(iterations < *greencounts)
		{
			P1OUT = 0x40; // GREEN LED On
			_delay_cycles(250000);
			P1OUT = 0x00; // GREEN LED off
			_delay_cycles(250000);
			iterations++;
		}
	    a = 1;
		return(a);
	}

int redledblink(int *redcounts)
	{
	    int a, iterations = 0;
	    while(iterations < *redcounts)
		{
			P1OUT = 0x01; // RED LED On
			_delay_cycles(250000);
			P1OUT = 0x00; // RED LED off
			_delay_cycles(250000);
			iterations++;
		}
	    a = 2;
		return(a);
	}

int toggleblink(int *togglecounts)
{
	int a, iterations = 0;
	P1OUT = 0x40;
	while(iterations < *togglecounts)
	{
		P1OUT ^= 0x41;
		_delay_cycles(250000);
		P1OUT ^= 0x41;
		_delay_cycles(250000);
		iterations++;
	}
	P1OUT = 0x00;
	a = 3;
	return(a);
}
int main (void)
{
	WDTCTL = WDTPW | WDTHOLD; //Stop Watchdog Timer
	P1DIR |= 0x41; //Configure LED1 and LED2 ports as Output
	P1OUT |= 0x00; // Green and Red LED are off
    int greencounts = 10, redcounts = 10, togglecounts = 10;
	_delay_cycles(2000000);
	green = greenledblink(&greencounts);
	_delay_cycles(2000000);
	red = redledblink(&redcounts);
	_delay_cycles(2000000);
	toggle = toggleblink(&togglecounts);
	_delay_cycles(2000000);
	return 0;
}
