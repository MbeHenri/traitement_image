#include "../../entete/stack/stack.h"
#include <stdlib.h>
#include <stdio.h>

stack new_stack(void){
    stack pile = malloc(sizeof(stack_element));
    pile->head = NULL;
    pile->nbre_element = 0;
    return pile;
}

boolean is_empty_stack(stack stk){
    if(stk->head == NULL){
        return True;
    }else{
        return False;
    }
}

void pop(stack stk, int* pe1 , int* pe2){
    if(is_empty_stack(stk) == True){
        //return NULL;
    }else{
        element *head_element = stk->head;
        //on met a jour la nouvelle tete de la pile
        stk->head = stk->head->next;
        *pe1 = head_element->e1;
        *pe2 = head_element->e2;
        free(head_element);
    }
}

void push(stack stk, int e1, int e2){
    stk->nbre_element += 1;   
    if(is_empty_stack(stk) == True){
        element *elem = malloc(sizeof(element));
        elem->e1 = e1;
        elem->e2 = e2;
        elem->next = NULL;
        stk->head = elem;
    }else{
        element *elem = malloc(sizeof(element));
        elem->e1 = e1;
        elem->e2 = e2;
        elem->next = stk->head;
        stk->head = elem;
    }
}

void free_stack(stack stk){
    while (is_empty_stack(stk) == False)
    {
        int a,b;
        pop(stk, &a, &b);
    }
    free(stk);
}
