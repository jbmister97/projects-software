#include <stdio.h>
#include <stdlib.h>


// Reverse all words in a string but leave the whitespace alone
char * reverse_words(char * str) {
    int length = 0;
    while(str[length] != '\0') {
        length++;
    }

    char * rev = (char *) malloc(sizeof(char) * length + 1);

    int start = 0, end = 0;
    while(start < length) {
        if(str[end] == ' ' || end == length) {
            int j = end - 1;
            for(int i = start; i < end; i++) {
                rev[i] = str[j];
                j--;
            }

            while(str[end] == ' ') {
                rev[end++] = ' ';
            }

            start = end;
            continue;
        }

        end++;
    }

    rev[length] = '\0';

    return rev;
}

// Reverse a certain word in the string
char * reverse_word(char * str, char * word) {

}

int main()
{
    char * str = "She sells seashells by the seashore";
    char * rev = reverse_words(str);
    printf("%s\n%s\n",str,rev);
    return 0;
}
