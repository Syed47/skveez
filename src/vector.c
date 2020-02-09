
#include "../headers/vector.h"


vector* new_vector()
{
	vector* v = malloc(sizeof(vector));
	v->vec = malloc(100 * sizeof(int));
	for (int i = v->i; i < v->size; ++i)
	{
		v->vec[i] = -1;
	}
	v->size = 100;
	v->i = 0;
	return v;
}

int vec_size(const vector* v)
{
	return v->i;
}

int vec_get(const vector* v, int i)
{
	return (i > -1) ? v->vec[i] : -1;
}

void vec_add(vector* v, int val)
{
	v->vec[v->i] = val;
	v->i++;
	if (v->i == v->size)
	{
		v->size += v->i;
		v->vec = realloc(v->vec, v->size);
		for (int i = v->i; i < v->size; ++i)
		{
			v->vec[i] = -1;
		}
		printf("realloc (%d)\n", v->size);
	}
}

int vec_is_empty(const vector* v)
{
	return v->i == 0;
}

void dis_vector(vector* v)
{
	free(v->vec);
	free(v);
	v->vec = NULL;
	v = NULL; // best practice
}
