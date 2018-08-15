#include <msp430.h> 

/*
 * HW7 #1h
 * y7[n] = y7[n-1] + x[n], n = 0 to 31, y7[-1] = 0 (Accumulator)
 *
 */
int i, check;
int range = 31;
int arrX[32];
int arrY[32];

int main(void) {
	arrX[0] = 16;
	for (i = 1; i <= range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
	}

	for (i = 0; i <= range; i++)
	{
		check = i - 1;
		if (check == -1)
		{
			arrY[check] = 0;
			arrY[i] = arrY[check] + arrX[i];
		}
		else{
		arrY[i] = arrY[i - 1] + arrX[i];
		}
	}
}
