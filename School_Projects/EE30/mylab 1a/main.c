/**************************************************************
 *  Lab 1a
 *  File: lab1a.c
 *  Objectives: Using CCS on LaunchPad for program development,
 *	        Exploring arithmetic operations.
 *
 * ***********************************************************/

#include <msp430g2553.h>

	int a, b, c;
	float d;
	long e;

void main(void)
{
	a = 25;
	b = 17;
	c = a + b;
	d = (b-a)/5.;
	e = (long) a * b;
}
