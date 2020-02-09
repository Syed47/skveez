
#include "../headers/stack.h"


STACK* new_STACK(const int size)
{
    if (size < 0) return NULL; 
    STACK* s = malloc(sizeof(STACK));
    s->ds    = calloc(size, sizeof(int));
    s->ptr   = 0;
    s->size  = size;

    return s;
}

void push(STACK *s, const int val)
{
    if (s->ptr == s->size) // inclusive size
    {
        printf("STACK full.\n");
    } else {
        s->ds[s->ptr] = val;
        s->ptr++;
    }
}

int pop(STACK *s)
{
    int o, i = s->ptr - 1;
    if (i == -1)
    {
        o = -1;
        puts("STACK is empty.");
    } else {
        o = s->ds[i];
        s->ds[i] = 0;
        s->ptr--;
    }
    return o;  
}

int peek(const STACK* s) // need improvement
{
    return s->ds[s->ptr];
}

int* STACK_as_array(const STACK* s)
{
    int size = s_maxsize(s);
    int* arr = malloc(sizeof(int) * size);

    int i = 0;
    while(i < size) 
    {
        arr[i] = s->ds[i];
        i++;
    }

    return arr;
}

void STACK_flip(STACK* s)
{
    int i = 0, size = s_maxsize(s) - 1;

    while(i < (size/2))
    {
        int t = s->ds[i];
        s->ds[i] = s->ds[size - i];
        s->ds[size - i] = t;
        i++;
    }
}

int s_maxsize(const STACK* s)
{   // this must be used inclusive (<=)
    return s->size;
}

void dis_STACK(STACK *s)
{
    free(s->ds);
    free(s);
    s->ds = NULL;
    s = NULL;
}
