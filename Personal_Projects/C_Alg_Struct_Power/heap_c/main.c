#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct heap
{
    int * arr;
    int size;
    int max;
};

typedef struct heap heap;

heap * create_heap(int max_size) {
    heap * h = (heap *) malloc(sizeof(heap));
    h->arr = (int *) malloc(sizeof(int) * max_size);
    h->size = 0;
    h->max = max_size;
    for(int i = 0; i < max_size; i++) {
        h->arr[i] = 0;
    }
    return h;
}

bool heap_empty(heap * h) {
    return h->size == 0;
}

void swap(int * n1, int * n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int max(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

int min(int n1, int n2) {
    return n1 > n2 ? n2 : n1;
}

void insert_max_heap(heap * h, int value) {
    h->arr[++h->size] = value;
    int child_index = h->size;
    while(child_index > 1 && h->arr[child_index] > h->arr[child_index/2]) {
        swap(&h->arr[child_index],&h->arr[child_index/2]);
        child_index = child_index/2;
    }
}

void insert_min_heap(heap * h, int value) {
    h->arr[++h->size] = value;
    int child_index = h->size;
    while(child_index > 1 && h->arr[child_index] < h->arr[child_index/2]) {
        swap(&h->arr[child_index],&h->arr[child_index/2]);
        child_index = child_index/2;
    }
}

int extract_max_heap(heap * h) {
    if(heap_empty(h)) {
        printf("Heap is empty");
        return -1;
    }
    int value = h->arr[1];
    h->arr[1] = h->arr[h->size];
    h->size--;
    int parent_index = 1;
    int left_child_index, right_child_index;
    do {
        left_child_index = parent_index * 2;
        right_child_index = parent_index * 2 + 1;
        if(h->arr[parent_index] > max(h->arr[left_child_index],h->arr[right_child_index])) {
            break;
        }
        if(h->arr[parent_index] == h->arr[left_child_index] || h->arr[left_child_index] > h->arr[right_child_index]) {
            swap(&h->arr[parent_index],&h->arr[left_child_index]);
            parent_index = left_child_index;
        }
        else {
            swap(&h->arr[parent_index],&h->arr[right_child_index]);
            parent_index = right_child_index;
        }
    } while(parent_index < h->size);

    return value;
}

int extract_min_heap(heap * h) {
    if(heap_empty(h)) {
        printf("Heap is empty");
        return -1;
    }

    int value = h->arr[1];
    h->arr[1] = h->arr[h->size];
    h->size--;
    int parent_index = 1;
    int left_child_index,right_child_index;
    do {
        left_child_index = parent_index * 2;
        right_child_index = parent_index * 2 + 1;
        if(h->arr[parent_index] < min(h->arr[left_child_index],h->arr[right_child_index])) {
            break;
        }
        if(h->arr[parent_index] == h->arr[left_child_index] || h->arr[left_child_index] < h->arr[right_child_index]) {
            swap(&h->arr[parent_index],&h->arr[left_child_index]);
            parent_index = left_child_index;
        }
        else {
            swap(h->arr[parent_index],h->arr[right_child_index]);
            parent_index = right_child_index;
        }
    } while(parent_index < h->size);

    return value;
}

int main()
{
    heap * max_h = create_heap(10);
    insert_max_heap(max_h,5);
    insert_max_heap(max_h,3);
    insert_max_heap(max_h,9);

    printf("Max heap size: %d\n", max_h->size);

    while(max_h->size > 0) {
        printf("%d ",extract_max_heap(max_h));
    }
    printf("\n");

    heap * min_h = create_heap(10);
    insert_min_heap(min_h,5);
    insert_min_heap(min_h,3);
    insert_min_heap(min_h,9);

    printf("Min heap size: %d\n", min_h->size);

    while(min_h->size > 0) {
        printf("%d ", extract_min_heap(min_h));
    }

    return 0;
}
