
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


void tree_add(NODE *root, int _val)
{
    if (_val < root->value)
    {
        if (root->left == NULL)
        {
            root->left = new_NODE(_val);
        }
        else
        {
            tree_add(root->left, _val);
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
            tree_add(root->right, _val);
        }
    }
}


void print_tree(const NODE* t, const char mode)
{
    printf((mode == 'c') ? "%c\n" : "%d\n", (t->value));


    if (t->left != NULL)
        print_tree(t->left, mode);
    

    if (t->right != NULL)
        print_tree(t->right, mode);  
}

void parse_tree(const NODE *t, vector* v)
{
    vec_add(v, t->value);
    if (t->left != NULL) 
    {
        parse_tree(t->left, v);
    }
    if (t->right != NULL) 
    {
        parse_tree(t->right, v);
    }
}

void track_tree(NODE* t, int* guide_lines, int i, int* out)
{
    if (i < 4)
    {
        *out = t->value;

        if (guide_lines[i] == 0)
        {
            track_tree(t->left, guide_lines, i + 1, out);
        } 
        if (guide_lines[i] == 1) 
        {
            track_tree(t->right, guide_lines, i + 1, out);
        }
    }
}

