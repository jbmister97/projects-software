#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_copy(char str1[], char str2[]) {
    int n1 = strlen(str1);
    int n2 = strlen(str2);

    //clear str2
    //(int i = 0; i < n2; i++)

    for(int i = 0; i < n1 + 1; i++) {
        str2[i] = str1[i];
    }
}

int main()
{
    printf("Hello world!\n");

    char str1[] = "Hello! =)";
    char str2[] = "Hello There adadwafwada";

    string_copy(str1,str2);

    printf("Str1: %s\nStr2: %s\n",str1,str2);
    return 0;
}
