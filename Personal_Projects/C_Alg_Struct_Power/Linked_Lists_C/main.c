#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// To execute C, please define "int main()"

struct list_node
{
  int value;
  struct list_node * next;
};
typedef struct list_node list_node;

struct list
{
  int count;
  list_node * head;
};
typedef struct list list;

list * create_list(void) {
  list * l = (list *) malloc(sizeof(list));
  l->count = 0;
  l->head = NULL;
  return l;
}

bool list_isempty(list * l) {
  return l->count == 0 || l->head == NULL;
}

void list_push_front(list * l, int value) {
  list_node * ln = (list_node *) malloc(sizeof(list_node));
  ln->value = value;
  ln->next = l->head;
  l->head = ln;
  l->count++;
}

void list_push_back(list * l, int value) {
  list_node * temp = l->head;
  while(temp->next != NULL) {
    temp = temp->next;
  }

  list_node * ln = (list_node *) malloc(sizeof(list_node));
  ln->value = value;
  ln->next = NULL;
  temp->next = ln;
  l->count++;
}

list_node * find_node(list * l, int value) {
  list_node * temp = l->head;
  while(temp != NULL) {
    if(temp->value == value) {return temp;}
    temp = temp->next;
  }
  return NULL;
}

void remove_node(list * l, int value) {
  list_node * curr_node = l->head;
  list_node * prev_node = l->head;

  while(curr_node != NULL){
    if(curr_node->value == value) {
      if(prev_node == curr_node) {
        prev_node = curr_node->next;
        free(curr_node);
        l->count--;
        return;
      }
      prev_node->next = curr_node->next;
      free(curr_node);
      l->count--;
      return;
    }
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
}

int main() {
  list * l = create_list();
  list_push_front(l,4);
  list_push_front(l,3);
  list_push_front(l,2);
  list_push_back(l,5);

  list_node * temp = l->head;
  while(temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }

  list_node * fn = find_node(l,3);
  printf("\nFound node with value %d\n",fn->value);

  remove_node(l,5);
  temp = l->head;
  while(temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }

  return 0;
}
