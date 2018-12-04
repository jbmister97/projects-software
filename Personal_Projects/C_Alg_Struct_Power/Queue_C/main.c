#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue based on linked list method

struct queue_node
{
  int value;
  struct queue_node * next;
};
typedef struct queue_node queue_node;

struct queue
{
  int count;
  queue_node * head;
  queue_node * tail;
};
typedef struct queue queue;

queue * create_queue(void) {
  queue * q = (queue *) malloc(sizeof(queue));
  q->count = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

bool queue_isempty(queue * q) {
  return q->count == 0 || q->head == NULL;
}

void queue_push(queue * q, int value) {
  queue_node * qn = (queue_node *) malloc(sizeof(queue_node));
  qn->value = value;
  qn->next = NULL;
  if(queue_isempty(q)) {
    q->head = qn;
    q->tail = qn;
    q->count++;
    return;
  }

  q->tail->next = qn;
  q->tail = qn;
  q->count++;
}

int queue_pop(queue * q) {
  if(queue_isempty(q)) {
    printf("Queue is empty!");
    return -1;
  }

  int value = q->head->value;
  queue_node * temp = q->head;
  q->head = q->head->next;
  free(temp);
  q->count--;
  return value;
}

int main() {
  queue * q = create_queue();
  queue_push(q,2);
  queue_push(q,3);
  queue_push(q,4);

  while(q->count) {
    printf("%d ", queue_pop(q));
  }

  return 0;
}
