
#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *ds;
    int ptr;
    int size;
} STACK;

STACK *new_STACK(const unsigned int size);

void push(STACK *s, const int val);

int pop(STACK* s);

void dis_STACK(STACK* s);

#endif