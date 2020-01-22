
#include "../headers/stack.h"


STACK* new_STACK(const int size)
{
    if (size < 0) return NULL; 
    STACK* s = malloc(sizeof(STACK));
    s->ds    = malloc(size * sizeof(int));
    s->ptr   = 0;
    s->size  = size;

    return s;
}

void push(STACK *s, const int val)
{
    if (s->ptr == s->size)
        printf("STACK full, item cannot be pushed.\n");
    else 
        s->ds[(s->ptr++)] = val;
}

int pop(STACK *s)
{
    return (int) s->ds[(--s->ptr)];
}

STACK* flipped(STACK* s)
{
    int i = s_size(s) - 1;
    // int* v = malloc(sizeof(int) * i);
    STACK* fs = new_STACK(i + 1);

    while(i > -1)
    {
        push(fs, pop(s));
        i--;
    }
    return fs;
}

int s_size(STACK* s)
{
    return s->size;
}

void dis_STACK(STACK *s)
{
    free(s->ds);
    free(s);
}
