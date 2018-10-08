#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



bool palindrome(char s[]) {
    int i = 0, j = strlen(s) - 1;

    while(i < j) {
        if(s[i] != s[j]) {return false;}
        else {
            j--;
            i++;
        }
    }

    return true;
}

int main()
{
    char s[] = "radar";

    printf("%s", palindrome(s) ? "true" : "false");
    return 0;
}
