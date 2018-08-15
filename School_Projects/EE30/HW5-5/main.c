#include <msp430g2553.h>
/*********
 * HW5 #5
 */
int x,num = 13,total;


int main()
{
	while(x < 12)
	{
		if(++num % 2 == 1)
		{
			total += num;
			x++;
		}
	}
}
