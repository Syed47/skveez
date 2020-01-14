
#include "../headers/stack.h"


STACK* new_STACK(const unsigned int size)
{

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
    return (int)s->ds[(--s->ptr)];
}

long s_size(STACK* s)
{
    return s->size;
}

void dis_STACK(STACK *s)
{
    free(s->ds);
    free(s);
}
