
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
	unsigned int size;
	unsigned int i; // index
	int* vec; // array
} vector;

vector* new_vector();
void    dis_vector();
int 	vec_size(const vector* v);
int     vec_get(const vector* v, int i);
void    vec_add(vector* v, int val);
int     vec_is_empty(const vector* v);

#endif