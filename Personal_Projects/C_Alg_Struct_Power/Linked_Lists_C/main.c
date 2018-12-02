#include <stdio.h>
#include <stdlib.h>

struct List_Node
{
    int value;
    struct List_Node * next;
};

typedef struct List_Node List_Node;

List_Node * create_list(int value) {
    List_Node * new_list = (List_Node *) malloc(sizeof(List_Node));
    new_list->value = value;
    new_list->next = NULL;
    return new_list;
}

void push_back(List_Node * list, int value) {
    while(list->next != NULL) {
        list = list->next;
    }
    List_Node * new_node = (List_Node *) malloc(sizeof(List_Node));
    new_node->next = NULL;
    new_node->value = value;
    list->next = new_node;
}

void push_front(List_Node * list, int value) {
    List_Node * node = (List_Node *) malloc(sizeof(List_Node));
    node->next = list->next;
    node->value = list->value;
    list->value = value;
    list->next = node;
}

int pop_back(List_Node * list) {
    if(list == NULL) {return 0;}
    if(list->next == NULL) {
        int val = list->value;
        list = NULL;
        return val;
    }

    while(list->next->next != NULL) {                                   // Stop at second to last node
        list = list->next;
    }
    List_Node * last = list->next;                                            // Create temp node for last node
    int value = last->value;
    free(last);
    list->next = NULL;                                                  // Break off last node from second to last node                                                // Delete the last node
    return value;
}

int pop_front(List_Node * list) {
    if(list->next == NULL) {
        int val = list->value;
        free(list);
        return val;
    }

    int value = list->value;
    List_Node * temp = list->next;
    list->value = list->next->value;
    list->next = list->next->next;
    free(temp);
    return value;
}

void free_list(List_Node * head) {
    List_Node * temp;

    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void insert(List_Node * l, int value) {

}

void remove(List_Node * l, int n) {

}

int main()
{
    List_Node * list = create_list(1);
    push_back(list,2);
    push_back(list,3);
    push_back(list,4);

    push_front(list,0);
    push_front(list,-1);
    push_front(list,-2);

    List_Node * temp = (List_Node *) malloc(sizeof(List_Node));
    temp = list;
    while(temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }

    /*
    pop_front(list);
    pop_front(list);
    pop_front(list);
    pop_front(list);
    pop_front(list);
    pop_front(list);
    int y = pop_front(list);
    printf("%d", y);
    */

    /*
    pop_back(list);
    pop_back(list);
    pop_back(list);
    pop_back(list);
    pop_back(list);
    pop_back(list);
    int x = pop_back(list);
    printf("%d",x);
    */

    free_list(list);

    return 0;
}
