
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

STACK* new_STACK(const int size);
void   push(STACK *s, const int val);
int    pop(STACK* s);
int    peek(const STACK* s);
int    s_maxsize(const STACK *s);
void   dis_STACK(STACK* s);
int*   STACK_as_array(const STACK* s);
void   STACK_flip(STACK* s); // free() required

#endif
