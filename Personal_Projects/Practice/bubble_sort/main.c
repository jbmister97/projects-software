#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int arr[], int n) {
    bool sorted = false;
    while(!sorted) {
        sorted = true;
        for(int i = 0; i < n - 1; i++) {
            if(arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;

                sorted = false;
            }
        }
    }
}

int main()
{
    printf("Hello world!\n");
    int arr[] = {2,3,5,4,1,9,8,4,5,3,2,7,5,3};
    int n = sizeof(arr) / sizeof(int);

    bubble_sort(arr,n);

    for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    return 0;
}
