#include <msp430.h> 

/*
 * HW7 #1g
 * y6[n] = 5/8*x[n], n = 0 to 31 (Amplifier/ Attenuator)
 *
 */
int i, range = 31;
int numerator;
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
		numerator = (arrX[i] << 2) + arrX[i];
		arrY[i] = numerator >> 3;
	}
}
