#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Stack using linked list method

struct stack_node
{
    int value;
    struct stack_node * next;
};

typedef struct stack_node stack_node;

struct stack
{
    int count;
    stack_node * top;
};

typedef struct stack stack;

stack * create_stack(void) {
    stack * s = (stack *) malloc(sizeof(stack));
    s->count = 0;
    s->top = NULL;
    return s;
}

bool stack_isempty(stack * s) {
    return s->count == 0 || s->top == NULL;
}

void stack_push(stack * s, int value) {
    stack_node * sn = (stack_node *) malloc(sizeof(stack_node));
    sn->value = value;
    if(stack_isempty(s)) {
        sn->next = NULL;
        s->top = sn;
        s->count++;
        return;
    }

    sn->next = s->top;
    s->top = sn;
    s->count++;
}

int stack_pop(stack * s) {
    if(stack_isempty(s)) {
        printf("Stack is empty");
        return -1;
    }

    int value = s->top->value;
    stack_node * temp = s->top;
    s->top = s->top->next;
    free(temp);
    s->count--;
    return value;
}

void stack_emptyall(stack * s) {
    while(!stack_isempty(s)) {
        stack_pop(s);
    }
}

int main()
{
    stack * s = create_stack();
    stack_push(s,3);
    stack_push(s,4);
    stack_push(s,5);

    while(s->count) {
        printf("%d ",stack_pop(s));
    }

    return 0;
}
