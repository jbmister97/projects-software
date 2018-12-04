#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Singly-Linked List

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

int list_pop_back(list * l) {
  list_node * back = l->head;
  int value;
  if(list_isempty(l)) {
    printf("List is empty");
    return -1;
  }
  if(back->next == NULL) {
    value = back->value;
    l->head = NULL;
    free(back);
    l->count--;
    return value;
  }

  while(back->next->next != NULL) {
    back = back->next;
  }

  value = back->next->value;
  list_node * temp = back->next;
  back->next = NULL;
  free(temp);
  l->count--;
  return value;
}

int list_pop_front(list * l) {
  if(l->count == 0) {
    printf("List is empty");
    return -1;
  }
  int value = l->head->value;
  list_node * temp = l->head;
  l->head = l->head->next;
  free(temp);
  l->count--;
  return value;
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
        l->head = curr_node->next;
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

void insert_node(list * l, list_node * prev, int value){
  list_node * ln = (list_node *) malloc(sizeof(list_node));
  ln->value = value;
  ln->next = prev->next;
  prev->next = ln;
  l->count++;
}

void display_list(list * l) {
  if(l->count == 0) {
    printf("List is empty");
    return;
  }

  list_node * temp = l->head;
  while(temp != NULL) {
    printf("%d ",temp->value);
    temp = temp->next;
  }
  printf("\n");
}

int main() {
  list * l = create_list();
  list_push_front(l,4);
  list_push_front(l,3);
  list_push_front(l,2);
  list_push_back(l,5);

  display_list(l);

  list_node * fn = find_node(l,3);
  printf("Found node with value %d\n",fn->value);

  remove_node(l,4);
  display_list(l);

  insert_node(l,find_node(l,2),7);
  display_list(l);

  list_pop_front(l);
  display_list(l);
  list_pop_front(l);
  display_list(l);
  list_pop_back(l);
  display_list(l);
  list_pop_back(l);
  display_list(l);

  return 0;
}
