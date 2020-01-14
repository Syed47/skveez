
#ifndef _MAP_H_
#define _MAP_H_

#include <stdlib.h>

typedef struct dictionary
{
    char character;
    int count;
    char* path;
} dictionary; // un-used yet

typedef struct MAP 
{
    int max_size;
    int index;
    char *keys;
    char* values;
} MAP;

MAP* new_MAP(int size);
void map_add(struct MAP* m,char* k, char* v);
int map_delete(struct MAP* m,char* k);
int map_update(struct MAP* m, char* k, char* nv);
void dis_map(struct MAP* m);
void log_map(struct MAP* m);
#endif