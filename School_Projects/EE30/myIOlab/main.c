/* LAB 3
 * Objective: Learn to control I/O ports on MSP230G2553
 * File: myIOlab.c
 */

 #include <msp430g2553.h>

#define red_LED   0x01

int BTN = 0x08;
long int delay = 265;
long int i;
int pressCnt = 0, incCnt = 0, timeCnt = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= red_LED;

    P1OUT = red_LED;

    P1OUT = 0x08;
    P1REN |= 0x08;

    while (1)
    {
    	i = delay;

    	while(i > 0) { i--;}

    	P1OUT ^= 0x01;
    	incCnt = 0;

        if ((P1IN & BTN) == 0)
           {
        		incCnt = 1;
        		pressCnt += incCnt;
        		delay += delay;
           }
        }
    }


