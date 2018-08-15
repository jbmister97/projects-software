#include <msp430.h> 

/*
 * main.c
 */



int main(void) {

	P1DIR |= BIT6;
	P1OUT |= BIT6;
	P1DIR |= BIT6 + BIT0;
	P1OUT ^= BIT6 + BIT0;
	P1OUT &= ~BIT0;

}
