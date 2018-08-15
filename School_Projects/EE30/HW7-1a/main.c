#include <msp430.h> 

/*
 * HW7 #1a
 * x[n] = -x[n-1], n = 1 to 31, x[0] = 16
 *
 */
int i;
int range = 31;
int arrX[32];

int main(void) {
	arrX[0] = 16;
	for (i = 1; i <= range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
	}

}
