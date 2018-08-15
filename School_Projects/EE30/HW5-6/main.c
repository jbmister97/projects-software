#include <msp430.h> 

/*
 * HW5 #6
 */
int x = 1,counter,total;

void main(void) {
    while(total < 144)
    {
    	total += x;
    	x += 2;
    	counter += 1;
    }
}

