#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

// REVERSE STRING FUNCTION

char * str_rev(char * str) {
  int length = 0;
  while(str[length] != '\0') {
    length++;
  }

  char * rev = (char *) malloc(sizeof(char) * length + 1);

  int end = length - 1;
  for(int i = 0; i < length; i++) {
    rev[i] = str[end];
    end--;
  }

  rev[length] = '\0';

  return rev;
}

int main() {

  //char str1[7] = "Hello!";
  //char str1[] = "Hello!";
  char * str1 = "Hello!";                     // String literal (NOT mutable)
  printf("%s\n",str1);
  char * rev = str_rev(str1);

  /*
  for(int i = 0; i < strlen(str1); i++) {
    str1[i] = rev[i];
  }
  */

  printf("%s\n",rev);
  return 0;
}
