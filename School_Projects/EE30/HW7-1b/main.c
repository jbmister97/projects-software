#include <msp430.h> 

/*
 * HW7 #1b
 * y1[n] = |x[n]|, n = 0 to 31
 */

int i, range = 31;
int arrX[32];
int arrY[32];
int main(void) {
	arrX[0] = 16;
	for (i = 1; i < range; i++)
	{
		arrX[i] = 0 - arrX[i - 1];
	}

	for (i = 0; i < range; i++)
	{

		if (arrX[i] & 0x8000 == 0)
		{
			arrY[i] = arrX[i];
		}
		else
		{
			arrY[i] = 16;
		}
	}

}
