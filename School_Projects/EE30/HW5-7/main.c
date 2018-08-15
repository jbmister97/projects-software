#include <msp430.h> 

/*
 * HW5 #7
 */
 int x = -16,s;

void main(void) {
	
  if(x & 0x8000 == 0)
  {
	  s = 0;
  }
  else
  {
	  s = 1;
  }
}
