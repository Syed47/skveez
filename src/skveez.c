
#include "../headers/skveez.h"

const unsigned int BYTE = 8;

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
        root->left = n_init(_val);
    else
        add(root->left, _val);
  }
  else if (_val > root->value)
  {
    if (root->right == NULL)
        root->right = n_init(_val);
    else
        add(root->right, _val);
  }
}

void find_bincode(Node *node, char c, int path[], int *found)
{
    if (node->value == ((int)c))
    {
        *found = 1;
    }
    size_t i;
    if (!(*found))
    {
        if (node->left != NULL)
        {
            for (i = 0; i < 8; i++)
            {
                if (path[i] == -1)
                {
                    path[i] = 0;
                    break;
                }
            }
            find_bincode(node->left, c, path, found);
            if (!(*found))
            {
                while (i < 8)
                {
                    path[i] = -1;
                }
            }
        }

        if (node->right != NULL)
        {
            for (i = 0; i < 8; i++)
            {
                if (path[i] == -1)
                {
                    path[i - 1] = 1;
                }
            }
            find_bincode(node->right, c, path, found);
            if (!(*found))
            {
                while (i < 8)
                {
                    path[i - 1] = -1;
                }
            }
        }
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

void compress_code(char *str, Node *t)
{
    unsigned int i = 0;

    while (str[i] != '\0')
    {
    }
}
