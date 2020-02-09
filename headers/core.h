
#ifndef _SKVEEZ_H_
#define _SKVEEZ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "stack.h"

void  skveez(const char* in_path, const char* out_path);
void  unskveez(const char* src, const char* dest);

void  write_tree_metadata(const char* path, const NODE* t);
NODE* optimised_tree(const char* data, int size);
NODE* metadata_to_tree(const char* path);
void  create_quartiles(const int* v, const int size, STACK* s);
int   cmp_chars(const void* a, const void* b);
void  _find_bincode(NODE* n, int c, int path[], int *found);
char* find_bincode(NODE* n, int c);

#endif
