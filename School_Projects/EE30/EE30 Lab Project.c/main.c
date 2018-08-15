#include <msp430.h> 

/*
 * EE30 Lab Project.c
 */
float x[90], maximum, minimum, period, sinefreq, squarefreq, dutycycle;
int check1, check2, check3, check4, test;
int gensig();
int sigparam();
int sqwgen();
int sqwparam();

int gensig()
{	int i, end1;
	for(i = 2; i < 90; i++)
	{P1OUT = 0x01;
		x[i] = (1.990379*x[i-1]) - (x[i-2]);
		_delay_cycles(10000);}
	P1OUT ^= 0x41;
	end1 = 1;
	return(end1);}

int sigparam()
{	int i, end2, count = 0, zero = 0;
	for(i = 0; i < 90; i++)
	{if(x[i] < minimum)
		{minimum = x[i];}
	if(x[i] > maximum)
		{maximum = x[i];}}
	for(i = 0; i < 90; i++)
	{count += 1;
		if((x[i] > -0.009) && (x[i] < 0.009))
		{zero += 1;}
		if(zero >= 3)
		{break;}}
	period = count * 0.01;
	sinefreq = 1 / period;
	end2 = 2;
	return(end2);
}

int sqwgen()
{	int i, end3;
	for (i = 0; i < 90; i++)
	{P1OUT = 0x01;
	_delay_cycles(10000);
		if (x[i] > 0.5)
		{x[i] = 1;}
		else
		{x[i] = 0;}}
	P1OUT ^= 0x41;
	end3 = 3;
	return(end3);
}

int sqwparam()
{	int i, end4;
	float ones, zeros;
	test = 0;
	ones = 0;
	zeros = 0;
	for (i = 0; i < 90; i++)
	{if ((test == 0) || (test == 1))
	{if (x[i] == 1.0)
	{ones += 1;
	test = 1;}}
	if ((test == 1) || (test == 2))
	{if (x[i] == 0.0)
	{zeros += 1;
	test = 2;}}
	if (test == 2)
	{if (x[i] == 1.0)
	{test = 3;}}
}
squarefreq = 1 / ((ones + zeros) * 0.01);
dutycycle = (ones / (ones + zeros)) * 100;
	end4 = 4;
	return(end4);
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR = 0x41;
    P1OUT = 0x00;
	x[0] = 0;
	x[1] = 0.0979676;
	check1 = gensig();
	maximum = -1;
	minimum = 1;
	check2 = sigparam();
	P1OUT = 0x00;
	check3 = sqwgen();
	check4 = sqwparam();
	return 0;
}
