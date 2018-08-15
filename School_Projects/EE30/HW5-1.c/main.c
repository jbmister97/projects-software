#include <msp430.h> 

/*
 * HW5 #1
 */

int x,y,remainder;

void main(void)
{
	x = 7;
	remainder = x % 2;
	if(remainder == 1)
	{ y = 1;
	}
	else
	{ y = 0;
	}

}
