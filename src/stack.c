
#include "../headers/stack.h"


STACK *new_STACK(const unsigned int size)
{
  int *ds = malloc(size * sizeof(int));
  int ptr = 0;

  STACK *s = malloc(sizeof(STACK));
  s->ds = ds;
  s->ptr = ptr;
  s->size = size;

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

long stack_size(STACK *s, int len)
{
  return sizeof(s) * len;
}

void dis_STACK(STACK *s)
{
  free(s);
}
