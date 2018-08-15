#include <msp430.h> 

/*
 * HW5 #4
 */

int cntr1,cntr0,num,total;

void main(void)
{	num = 0;
	while (total<16){
		if(num & 0x0001 == 0)
			{
			cntr1++;}
		else{
			cntr0++;
		}
		total++;
		num >> 1;
	}
}
