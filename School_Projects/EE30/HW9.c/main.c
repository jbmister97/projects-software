#include <msp430.h> 

/*
 * HW #9
 */

int a = 7, b = 8, c = 9;
int arr[5] = {89,134,67,222,467};
long int sum, Arrsum = 0;
int i, x = 4, y;
float product, fpn = 4.3;
int sqr(int *x);
long int sum3(int a, int b, int c);

long int sum3(int a, int b, int c)
{	sum = a + b + c;
	return sum;	}

long int sumArr(int arr[])
{	for (i = 0; i < 5; i++)
	{
		Arrsum += arr[i];
	}
	return Arrsum;	}
float mul3(int a, int b, float fpn)
{	product = a * b * fpn;
	return product;	}

int sqr(int *x)
{	y = *x * *x;
	return y;	}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	sum3(a, b, c);
	sumArr(arr);
	mul3(a, b, fpn);
	sqr(&x);

	return 0;
}


