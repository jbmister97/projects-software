#include <stdio.h>
#include <stdbool.h>

// Print numbers in array that are a power of 2

void if_power2(int * arr, int length) {
  int n;
  bool is_power;
  for(int i = 0; i < length; i++) {
    n = arr[i];
    is_power = true;
    while(n != 1) {
      if(n%2 != 0) {is_power = false;}
      n /= 2;
    }
    if(is_power && arr[i] >= 2) {printf("%d ",arr[i]);}
  }
}

int main() {

  int arr[] = {1,2,3,4,5,6,7,8,9,10,14,15,16,28,29,31,32,62,63,64,65};
  int length = sizeof(arr)/sizeof(arr[0]);
  if_power2(arr,length);

  return 0;
}
