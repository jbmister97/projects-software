#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if(n == 1) {return 1;}

    int num = factorial(n - 1);

    return n * num;
}


int main()
{
    printf("Hello world!\n");

    int num = factorial(5);

    printf("%d", num);

    return 0;
}
