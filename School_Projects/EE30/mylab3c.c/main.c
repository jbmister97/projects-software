/* LAB 3C
 * Objective: Learn to control I/O ports on MSP230G2553
 * File: lab3c.c
 */

 #include <msp430g2553.h>

#define red_LED   0x01
#define grn_LED   0x40
#define BTN   	0x08

unsigned int i;
int chanceCnt = 0, pressCnt = 0, timeCnt = 0, incCnt = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                    		// turn off watch-dog timer
	P1DIR |= red_LED + grn_LED;                		// LED pins to outputs, PUSH BTN
                             	                           			// is still an input by default.
    P1OUT = 0;                                                                   	// turn off both LEDs

    P1OUT = 0x08;                 	       			// P1.3 set
    P1REN |= 0x08;                	       			// P1.3 pullup

    do
    {
    	for (i = 0; i < 2; i++)         	            			// blink red LED twice
    	            	{
    	                            	P1OUT |= red_LED;
    	        		_delay_cycles(500000);
    	        		P1OUT &= ~red_LED;
    	        		_delay_cycles(500000);
    	            	}
    	  	      	_delay_cycles(500000);                		// wait a bit
    	            	P1OUT |= grn_LED;	                    		// turn green LED on -
    	                                                                                            	// time to press the button
    	            	incCnt = 0;
    	            	timeCnt = 0;
    	            	do
    	            	{
    	            		if ((P1IN & BTN) == 0)     			// incCnt = 1 if button pressed
    	                                            	{incCnt = 1;}
    	                                            	timeCnt++;
    				_delay_cycles(100);
    	            	}while (timeCnt < 20000);

    	                            	P1OUT &= ~grn_LED;                   		// green LED off

    	                            	pressCnt += incCnt;                        		// update the counts
    	                            	chanceCnt++;

    }while (chanceCnt < 10);

}
