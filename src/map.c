
#include "../headers/map.h"
#include <stdio.h>

MAP *new_MAP(int size)
{
    MAP *m = malloc(sizeof(MAP));
    m->max_size = size;
    m->index    = 0;
    m->keys     = calloc(size, sizeof(char));
    m->values   = calloc(size, sizeof(char));

    return m;
}


void map_add(struct MAP* m, char *k, char *v)
{
    for (int i = 0; i < m->max_size; ++i)
    {
        if (m->keys[i] == 0)
        {
            m->keys[i] = *k;
            m->values[i] = *v;
            i = m->max_size;
        }
    }
    // m->index++;
}

int map_update(struct MAP *m, char *k, char* nv)
{
    for (int i = 0; i < m->max_size; ++i)
    {
        if (m->keys[i] == *k)
        {
            m->values[i] = *nv;
            i = m->max_size;
        }
    }
    return 1;
}

int map_delete(struct MAP* m,char *k)
{
    int exist = 0;
    for (int i = 0; i < m->max_size; ++i)
    {
        if (m->keys[i] == *k)
        {
            m->keys[i] = 0;
            m->values[i] = 0;
            exist = 1;
            // m->index--;
        }
    }
    return exist;
}

void log_map(struct MAP *m)
{
    for (int i = 0; i < m->max_size; ++i)
    {
        printf("%c : %c\n", m->keys[i], m->values[i]);
    }
}

void dis_map(struct MAP *m)
{
    free(m->keys);
    free(m->values);
    free(m);
}
