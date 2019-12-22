
#ifndef _SKVEEZ_H_
#define _SKVEEZ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

/*-----------------------<DECLARATION>---------------------------*/

int f_size;

Node *n_init(int _val);

void add(Node *root, int _val);

void find_bincode(Node *node, char c, int path[], int *found);

void parse_r(Node *node);

int *rnumg(int from, int to, int smpl);

int get_fsize(FILE *f);

char *load_file(const char *path);

void printcc(char *arr, int len);

void bin_code(char *str);

void compress_code(char *str, Node *t);

#endif