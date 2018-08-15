#include <msp430.h> 

/*
 * HW7 #1d
 * y3 = sum of y1[n], n = 0 to 31 (Integrator)
 *
 */
int i, y3, check, range = 31;
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
		if (arrX[i] & 0x8000 == 0)
		{
			arrY[i] = arrX[i];
		}
		else
		{
			arrY[i] = 16;
		}
		y3 += arrY[i];
	}
}
