
#include "../headers/skveez.h"
#include "../headers/map.h"
#include <string.h>

const unsigned int BYTE = 8;


// static dictionary* create_char_map(char c, int count, char* path)
// {
//     return void
// }


Node *n_init(int _val)
{
    Node *r = malloc(sizeof(Node));
    r->left = NULL;
    r->right = NULL;
    r->value = _val;
    return r;
}

void add(Node *root, int _val)
{
    if (_val < root->value)
    {
        if (root->left == NULL)
        {
            root->left = n_init(_val);
        } else {
            add(root->left, _val);
        }
    }
    else if (_val > root->value)
    {
        if (root->right == NULL)
        {
            root->right = n_init(_val);
        } else {
            add(root->right, _val);
        }
    }
}

void find_bincode(Node *node, int c)
{ // need to return the path or should add the path to the MAP struct
    int found = 0;
    int node_trace[BYTE] = {-1, -1, -1, -1, -1, -1, -1, -1};
    char path[8] = "";
   
    _find_bincode(node, c, node_trace, &found);
    
    if (found) {
        for (int i = 0; i < BYTE; ++i)
        {
            if (node_trace[i] == 1) {
                strcat(path, "1");
            } else if (node_trace[i] == 0) {
                strcat(path, "0");
            }
        }

        printf("Character: %c | Skveez Code: %s | Length: %lu | Found: %s\n\n", 
            (char) c, 
            path, 
            strlen(path), 
            found ? "TRUE" : "FALSE"
        );

    } else {
        printf("\n<%c> Not Found.\n\n", (char) c);
    }
}

static void _find_bincode(Node *node, int c, int* path, int *found)
{
    int i = 0;

    if (node->value == c) *found = 1;

    if (node->left != NULL && !(*found))
    {
        while (i < BYTE)
        {
            if (path[i] == -1) {
                path[i] = 0;
                break;
            } else {
                i++;
            }
        }

        _find_bincode(node->left, c, path, found);

        if (!(*found)) path[i] = -1;
    }

    if (node->right != NULL && !(*found))
    {
        while(i < BYTE)
        {
            if (path[i] == -1) {
                path[i] = 1;
                break;
            } else {
                i++;
            }
        }

        _find_bincode(node->right, c, path, found);

        if (!(*found)) path[i] = -1;
    }
}

void parse_r(Node *node)
{
    if (node->right != NULL)
        parse_r(node->right);

    printf("%d\n", node->value);

    if (node->left != NULL)
        parse_r(node->left);
}

int *rnumg(int from, int to, int smpl)
{
    int *nums = malloc(sizeof(from) * smpl);
    srand(time(NULL));
    int r;

    for (int i = 0; i < smpl; ++i)
    {
        r = (rand() % to) + from;
        nums[i] = r;
    }

    return nums;
}

int get_fsize(FILE *f)
{
    int size = 0; // number of characters
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

char *load_file(const char *path)
{
    FILE *f = fopen(path, "r");
    int size = get_fsize(f);
    int bytes = sizeof(char) * size;
    char *all = malloc(bytes);
    char *buffer = malloc(bytes);

    f_size = size;

    while (f && fgets(buffer, size, f) != NULL)
    {
        strcat(all, buffer);
    }

    free(buffer);
    fclose(f);


    

    return all;
}

void printcc(char *arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%c : %d\n", arr[i], ((int)arr[i]));
    }
}

/* 
	Seems to work fine for now but need to be more robust 
	and need to go through proper testing.
*/
void bin_code(char *str)
{
    int len = strlen(str);
    int bins[BYTE] = {}; // Array for flipping remainders
    for (int i = 0; i < len; ++i)
    {
        int index = 0;
        int den = (int)str[i];
        while (den > 0)
        {
            int mod = den % 2;
            bins[index++] = mod;
            den /= 2;
        }
        //
        for (int i = BYTE - 1; i > -1; i--)
        {
            printf("%d", bins[i]);
        }
        printf(" ");
    }
    printf("\n");
}

// when need to compress a string rather than a character
void compress_code(char *str, Node *t)
{
    unsigned int i = 0;

    while (str[i] != '\0')
    {
    }
}
