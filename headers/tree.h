
#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include "../headers/vector.h"

// NEED A FUNCTION TO FREE ALLOCATED MEMORY FOR THIS TREE

typedef struct NODE
{
    int value;
    struct NODE *left;
    struct NODE *right;
} NODE;

NODE *new_NODE(int _val);
void tree_add(NODE *root, int _val);
int* tree_array(const NODE* t);
void parse_tree(const NODE* t, vector* v);
void track_tree(NODE* t, int* guide_lines, int i, int* out);
void print_tree(const NODE* t, const char mode);
void dis_NODE(NODE* t);

#endif