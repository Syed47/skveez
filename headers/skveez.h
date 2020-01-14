
#ifndef _SKVEEZ_H_
#define _SKVEEZ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int f_size;

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;


Node* n_init(int _val);
void  add(Node *root, int _val);
static void _find_bincode(Node *node, int c, int path[], int *found);
// static dictionary* create_char_map(char c, int count, char* path);
void find_bincode(Node *node, int c);
void parse_r(Node *node);
int*  rnumg(int from, int to, int smpl);
int   get_fsize(FILE *f);
char* load_file(const char *path);
void  printcc(char *arr, int len);
void  bin_code(char *str);
void  compress_code(char *str, Node *t);

#endif
