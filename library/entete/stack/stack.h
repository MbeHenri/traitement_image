#ifndef STACK_H
#define STACK_H
#include "structure.h"

typedef struct stack
{
    int nbre_element;
    element *head;

}*stack , stack_element;

stack new_stack(void);
boolean is_empty_stack(stack stk);
void pop(stack stk, int* pe1 , int* pe2);
void push(stack stk , int e1, int e2);
void free_stack(stack stk);

#endif