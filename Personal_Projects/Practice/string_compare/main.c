#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str1        "Hello";

int compareStr(char *str1, char *str2) {
    int i = 0;

    while(str1[i] != '\0' || str2[i] != '\0') {
        if(str1[i] == '\0' || str2[i] == '\0') {return str1[i] - str2[i];}
        if(str1[i] != str2[i]) {return str1[i] - str2[i];}
        i++;
    }
    return 0;
}

int main()
{
    //char *str1 = "Hello";
    char *str2 = "Hello";

    int equal = compareStr(str1, str2);

    if(equal == 0) {
        printf("Strings were equal");
    }
    else {
        printf("Strings were not equal: %d",equal);
    }
    return 0;
}
