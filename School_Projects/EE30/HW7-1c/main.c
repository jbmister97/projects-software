#include <msp430.h> 

/*
 * HW7 #1c
 * y2[n] = x[n] – x[n-1], n = 1 to 31, y2[0] = x[0] (Differentiator)
 *
 */
int i;
int range = 31;
int arrX[32];
int arrY[32];

int main(void) {
	arrX[0] = 16;
	for (i = 1; i <= range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
		arrY[i] = arrX[i] - arrX[i - 1];
	}

	
}

