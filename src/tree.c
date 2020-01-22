
#include <stdlib.h>
#include <stdio.h>
#include "../headers/tree.h"

NODE *new_NODE(int _val)
{
    NODE *r = malloc(sizeof(NODE));
    r->left = NULL;
    r->right = NULL;
    r->value = _val;
    return r;
}

void dis_NODE(NODE* t)
{
    if (t->left != NULL)
    {
        dis_NODE(t->left);
        free(t->left);
    }
    if (t->right != NULL)
    {
        dis_NODE(t->right);
        free(t->right);
    }
    free(t); 
}


void add(NODE *root, int _val)
{
    if (_val < root->value)
    {
        if (root->left == NULL)
        {
            root->left = new_NODE(_val);
        }
        else
        {
            add(root->left, _val);
        }
    }
    else if (_val > root->value)
    {
        if (root->right == NULL)
        {
            root->right = new_NODE(_val);
        }
        else
        {
            add(root->right, _val);
        }
    }
}

void parse_tree(NODE *NODE)
{
    printf("%c\n", ((char)NODE->value));

    if (NODE->left != NULL)
        parse_tree(NODE->left);

    if (NODE->right != NULL)
        parse_tree(NODE->right);
}