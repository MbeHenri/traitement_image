#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef enum boolean
{
    True = 0,
    False = 1
} boolean;

typedef struct element
{
    int e1;
    int e2;
    struct element *next;
}element;

#endif