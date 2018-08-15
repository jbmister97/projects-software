#include <msp430.h> 

/*
 * HW7 #3
 * Add and Subtract two matrices
 *
 */
int matA[2][3] = {4,5,6,7,8,2};
int matB[2][3] = {2,4,3,3,2,5};
int i, j, sumAB[2][3], diffAB[2][3];

int main(void) {
    for (i = 0; i < 2; i++)
    {
    	for (j = 0; j <3; j++)
    	{
    		sumAB[i][j] = matA[i][j] + matB[i][j];
    		diffAB[i][j] = matA[i][j] - matB[i][j];
    	}
    }

}
