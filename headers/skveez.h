
#ifndef _SKVEEZ_H_
#define _SKVEEZ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tree.h"
#include "stack.h"

void  skveez(const char* data, const char* d);
NODE* optimised_tree(const char* data, int size);
void  create_quartiles(const int* v, const int size, STACK* s);
int   cmp_chars(const void* a, const void* b);
int*  to_set(const int* n, const int size);
void  _find_bincode(NODE* NODE, int c, int path[], int *found);
void  proto_compress(char* data);
char* find_bincode(NODE *NODE, int c);
int*  rnumg(int from, int to, int smpl); // free() required
int   get_fsize(FILE *f);
char* load_file(const char* path); // free() required
void  write_file(const char* fname, const char* data);
void  printcc(char *arr, int len);
void  bin_code(const char *str);
int   bin_to_decimal(const char* bincode);
char* bin_to_char(const char* bincode);

#endif
