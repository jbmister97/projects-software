#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct queue_node
{
    int value;
    struct queue_node * next;
};

typedef struct queue_node queue_node;

struct queue
{
    queue_node * front;
    queue_node * back;
    int size;
};

typedef struct queue queue;

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

int main()
{
    queue * q = create_queue();

    push_queue(q,3);
    push_queue(q,4);
    push_queue(q,5);

    for(int i = 0; i < q->size; i++) {
        printf("%d ", pop_queue(q));
    }

    return 0;
}
