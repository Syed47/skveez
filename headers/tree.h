
#ifndef _TREE_H_
#define _TREE_H_

// NEED A FUNCTION TO FREE ALLOCATED MEMORY FOR THIS TREE

typedef struct NODE
{
    int value;
    struct NODE *left;
    struct NODE *right;
} NODE;

NODE *new_NODE(int _val);
void add(NODE *root, int _val);
void parse_tree(NODE* NODE);
void dis_NODE(NODE* t);

#endif