#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct pair
{
    int val;
    int index;
} pair;

void sort(pair arr[], int size) {

    bool sorted = false;

    while(!sorted) {
        sorted = true;
        for(int i = 0; i < size; i++) {
            printf("%d ",arr[i].val);
        }
        printf("\n");
        for(int i = 0; i < size - 1; i++) {
            if(arr[i].val > arr[i+1].val) {
                int temp_val = arr[i].val;
                int temp_index = arr[i].index;
                arr[i].val = arr[i+1].val;
                arr[i].index = arr[i+1].index;
                arr[i+1].val = temp_val;
                arr[i+1].index = temp_index;
                sorted = false;
            }
        }
    }
}

char * my_strcat(char *s1, const char *s2) {
    int size = strlen(s1) + strlen(s2) + 2;
    char *s3 = (char *) malloc(sizeof(char) * size);
    int i = 0, j = 0;
    while(s1[i] != '\0') {
        s3[i] = s1[i];
        i++;
    }
    s3[i++] = ' ';

    while(s2[j] != '\0') {
        s3[i+j] = s2[j];
        j++;
    }

    s3[i+j] = '\0';

    return s3;
}

int main()
{
    printf("Hello world!\n");

    int arr2[4] = {2, 11, 7, 15};
    int arr2_size = sizeof(arr2)/sizeof(int);

    pair *sorted = (pair *) malloc(sizeof(pair) * arr2_size);

    for(int i = 0; i < arr2_size; i++) {
        sorted[i].val = arr2[i];
        sorted[i].index = i;
    }

    sort(sorted, arr2_size);

    for(int i = 0; i < arr2_size; i++) {
        printf("Val: %d Index: %d\n", sorted[i].val,sorted[i].index);
    }


    char s1[] = "hello";
    char s2[] = "world";

    char *s3 = my_strcat(s1,s2);

    printf("%s", s3);

    free(s3);
    return 0;
}
