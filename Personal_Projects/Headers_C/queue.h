#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

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

bool queue_empty(queue * q);
queue * create_queue(void);
void push_queue(queue * q, int x);
int pop_queue(queue * q);

#endif // QUEUE_INCLUDED
