#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

bool queue_empty(queue * q) {
    return (q->size == 0) || (q->front == NULL);
}

queue * create_queue(void) {
    queue * q = (queue *) malloc(sizeof(queue));
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

void push_queue(queue * q, int x) {
    queue_node * qn = (queue_node *) malloc(sizeof(queue_node));
    qn->value = x;
    qn->next = NULL;
    if(queue_empty(q)) {
        q->front = qn;
        q->back = qn;
        q->size++;
        return;
    }

    q->back->next = qn;
    q->back = qn;
    q->size++;
}

int pop_queue(queue * q) {

    if(queue_empty(q)) {
        printf("Queue is empty");
        return 0;
    }
    int val = q->front->value;

    queue_node * temp = q->front;
    q->front = q->front->next;
    free(temp);
    return val;
}
