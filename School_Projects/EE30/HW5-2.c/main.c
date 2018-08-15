#include <msp430.h> 

/*
 *HW5 #2
 */

int num = 600,binary;


void main(void)
{
	binary = ((num & 0xF000) >> 12) * 1000;
	binary = binary + ((num & 0x0F00) >> 8) * 100;
	binary = binary + ((num & 0x00F0) >> 4) * 10;
	binary = binary + (num & 0x000F);
}
