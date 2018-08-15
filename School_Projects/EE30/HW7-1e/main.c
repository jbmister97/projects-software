#include <msp430.h> 

/*
 * HW #1e
 * e)	y4[n] = x[2n], n = 0 to 15 (Compressor)
 *
 */
int i, range = 31;
int arrX[32];
int arrY[32];
int main(void) {
	arrX[0] = 16;
	for (i = 1; i <= range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
	}
	for (i = 0; i <= 15; i++)
	{
		arrY[i] = arrX[2 * i];
	}
}
