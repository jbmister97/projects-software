/**************************************************************
 *  Lab 1b
 *  File: lab1b.c
 *  Objectives: Using CCS on LaunchPad for program development,
 *	        Exploring bitwise operations.
 *
 * ***********************************************************/

#include <msp430g2553.h>

	int a, b, c;
	

void main(void)
{
	a = 0x15;
	b = 0x2A;
	c = a|b;
	c = a & b;
	c = a ^ b;
	c = ~a;
	c = a >> 4;
	c = b << 2;
}
