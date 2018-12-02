#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * str_rev(char *str) {
    int size = strlen(str);
    char *str_new = (char *) malloc(size + 1);
    int i = 0, j = size - 1;
    char temp;

    while(i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    str[size] = '\0';
    /*
    int j = size - 1;

    for(int i = 0; i < size; i++) {
        str_new[i] = str[j];
        j--;
    }
    str_new[size] = '\0';
    */

    return str_new;
}

int main()
{
    char str[] = "Hello there!";
    //char *str_reversed = str_rev(str);

    //printf("Before: %s After: %s\n", str, str_reversed);

    str_rev(str);
    printf("%s", str);

    //free(str_reversed);
    return 0;
}
