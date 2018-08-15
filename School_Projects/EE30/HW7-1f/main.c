#include <msp430.h> 

/*
 * HW7 #1f
 * y5[n] = 1/3*(x[n] + x[n-1] + x[n-2]), n = 2 to 31, y5[0] = y5[1] = 0 (Moving Averager)
 *
 */
int i, range = 31;
int b;
int arrX[32];
float arrY[32];

int main(void) {
	arrX[0] = 16;
	arrY[0] = 0;
	arrY[1] = 0;
	for (i = 1; i <= range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
	}
	for (i = 2; i <= range; i++)
	{
		b = arrX[i] + arrX[i - 1] + arrX[i - 2];
		arrY[i] = b / 3.;
	}

}
