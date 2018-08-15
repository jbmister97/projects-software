/**************************************************************
 *  Lab1c
 *  File: lab1c.c
 *  Objectives: Using CCS on LaunchPad for program development,
 *	        Exploring operations.
 *
 * ***********************************************************/

#include <msp430g2553.h>

	int a, b;
	

void main(void)
{
	a = 45;
	b = 8;
	a++;
	--b;
	a += b;
	a -= b;
	a *= b;
	a /= b;
	a %= b;
}
