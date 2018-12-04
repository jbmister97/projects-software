#include <stdio.h>
#include <stdlib.h>

void flag_sort(int * arr, int length) {

    int right = 0, mid = 0, left = length-1;
    int temp;

    while(mid <= left) {
        if(arr[mid] == 0) {
            temp = arr[mid];
            arr[mid++] = arr[right];
            arr[right++] = temp;
            continue;
        }
        if(arr[mid] == 1) {
            mid++;
            continue;
        }
        if(arr[mid] == 2) {
            temp = arr[mid];
            arr[mid] = arr[left];
            arr[left--] = temp;
            continue;
        }
    }
}

int main()
{
    int arr[] = {0,0,1,2,2,0,1,2,1,1,2,2,0,0,2,1,2,2,1,0,2,0,2,1,0};
    int length = sizeof(arr)/sizeof(arr[0]);
    printf("Size of array: %d\n",length);
    flag_sort(arr,length);

    for(int i = 0; i < length; i++) {
        printf("%d",arr[i]);
    }
    return 0;
}
