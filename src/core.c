#include "../headers/util.h"
#include "../headers/tree.h"
#include "../headers/stack.h"
#include "../headers/core.h"

const unsigned int BYTE = 8;
int f_size = 0, cmpd_size = 0;

void unskveez(const char* src, const char* dest)
{
    NODE* mt = metadata_to_tree(src);
    char** raw_data = read_file_lines(src, 1, 2);
    char*  data = raw_data[1];
    puts(data);
    unsigned int data_size = strlen(data);
    print_tree(mt, 'c');
    puts("______________");
    for (int i = 0; i < data_size; ++i)
    {
        int x = (int) data[i];
        int* bins = int_bincode(x);
        for (int i = 0; i < 8; ++i)
        {
            printf("%d", bins[i]);
        }
        puts("");
        int* a = &bins[0];
        int* b = &bins[4];

        for (int i = 0; i < 4; ++i)
        {
            printf("%d", a[i]);
        }
        puts("");
        for (int i = 0; i < 4; ++i)
        {
            printf("%d", b[i]);
        }
        puts("");
        int x1, x2; 
        track_tree(mt, a, 0, &x1);
        track_tree(mt, b, 0, &x2);
        printf("%d | %d\n\n", x1, x2);
    }    
}


NODE* metadata_to_tree(const char* path)
{
    const int lns = 1;
    char** lines = read_file_lines(path, 0, lns);

    // NODE* t = optimised_tree(lines[0], strlen(lines[0]));
    NODE* t = new_NODE(lines[0][0]); // THIS METHOD SEEMS FASTER
    int len = strlen(lines[0]);
    
    for (int i = 1; i < len; ++i)
    {
        tree_add(t, lines[0][i]);
    }

    return t;
}


void skveez(const char* in_path, const char* out_path)
{
    char* raw_data = load_file(in_path);
    printf("FILE SIZE %lu\n", strlen(raw_data));
    f_size = (int) strlen(raw_data);
    if (!f_size) exit(1);
    cmpd_size = ((f_size) / 2) + 1; 

    NODE* char_tree = optimised_tree(raw_data, f_size);
    write_tree_metadata(out_path, char_tree);

    char codes[f_size][(BYTE/2) + 1];
    char out_data[cmpd_size];

    for (int i = 0; i < f_size; ++i)
    {
        char* sc = find_bincode(char_tree, raw_data[i]);
        strcpy(codes[i], sc);
        codes[i][(BYTE/2)] = '\0';
        // free(sc); // DO NOT FREE THIS MEMORY (ASK STACK-OVERFLOW)
    }

    const int loops = f_size % 2 == 0 ? f_size : f_size - 1;

    for (int i = 0; i <= loops; i += 2)
    {   
        char pair_code[BYTE + 1];
        strcpy(pair_code, codes[i]);
        strcat(pair_code, codes[i + 1]);
        pair_code[BYTE] = '\0';

        char ascii_code = bin_to_decimal(pair_code);

        if (ascii_code <= 32) 
        {
            ascii_code += 33;
        }

        out_data[i/2] = ascii_code;
    }

    // write_tree_metadata("cmpd.txt", );
    append_file(out_path, out_data);

    char* compressed_data = load_file(out_path);

    double raw_size = (double) strlen(raw_data);
    double cmpd_size = (double) strlen(compressed_data);
    double rate = (raw_size - cmpd_size) / raw_size * 100;

    printf("\nOriginal Size:    %.0f\n", raw_size);
    printf("Compressed Size:  %.0f\n", cmpd_size);
    printf("Compression Rate: %0.2f %%.\n", rate);

    // dis_NODE(char_tree);
    // free(raw_data);
    // free(compressed_data);

    // puts("\nSKVEEZED!");

    // NODE* mt = metadata_to_tree(out_path);
    // print_tree(mt, 'd');
    // puts(s);
}

void write_tree_metadata(const char* path, const NODE* t)
{
    vector* vec = new_vector();
    parse_tree(t, vec);

    int len = vec_size(vec);
    char xs[len + 1];
    strcpy(xs, ""); // (or xs[0] = 0;) assignment to an empty string

    for (int i = 0; i < len; ++i)
    {
        char o = (char)vec_get(vec, i);
        if (o == '\0' || o == '\n') o+= 33;
        xs[i] = o;
    }

    xs[len] = '\0';

    write_file(path, xs);
    append_file(path, "\n");
    dis_vector(vec);
}

void create_quartiles(const int* set, const int size, STACK* s)
{
    int mid = (int)(size / 2);
    int left_size = mid, right_size = size - (mid + 1);
    int left[left_size], right[right_size];
    push(s, set[mid]);

    for (int i = 0; i < mid; ++i)
    {
        if (i < left_size) {
            left[i] = set[i];
        }
        if (i < right_size) {
            right[i] = set[(mid + 1) + i];
        }
    }

    if (size > 0)
    {
        if (left_size)
            create_quartiles(left, left_size, s);
    
        if (right_size)
            create_quartiles(right, right_size, s);
    }
} 

int cmp_chars(const void* a, const void* b)
{
    return (*(int *)a - *(int *)b);
}

NODE* optimised_tree(const char* data, int _size)
{
    int size = _size + 1;
    int ascii_codes[size];
    ascii_codes[size] = '\0';

    for (size_t i = 0; i < size; ++i)
    {
        ascii_codes[i] = data[i];
    }
    
    // Sorting ASCII codes
    qsort(ascii_codes, size, sizeof(int), cmp_chars);
    
    int* unq_ascii_codes = array_to_set(ascii_codes, size);
    int set_size = 0;
    
    for (int i = 0; i < size; ++i)
    {
        set_size += (unq_ascii_codes[i] != -1 && 
                    unq_ascii_codes[i] < 128) ? 1 : 0;
    }

    STACK* qs = new_STACK(set_size);
    create_quartiles(unq_ascii_codes, set_size, qs);
    STACK_flip(qs); // Important unskveezing
    NODE* opt_tree = new_NODE(pop(qs));

    for (int i = 1; i < set_size; ++i)
    {
        tree_add(opt_tree, pop(qs));
    }

    free(unq_ascii_codes);
    dis_STACK(qs);

    return opt_tree;
}


char* find_bincode(NODE* node, int c)
{
    int found = 0, code_len = (BYTE / 2) + 1;
    char* path = malloc(code_len * sizeof(char));
    int node_trace[BYTE] = {-1, -1, -1, -1, -1, -1, -1, -1};

    _find_bincode(node, c, node_trace, &found);

    if (found) {
        for (int i = 0; i < BYTE; ++i)
        {
            if (node_trace[i] == 1) {
                strncat(path, "1", code_len);
            } else if (node_trace[i] == 0) {
                strncat(path, "0", code_len);
            }
        }

        path[code_len - 1] = '\0';

        printf("Character: %c | Skveez Code: %s | Length: %lu | Found: %s\n\n", 
            (char) c, 
            path, 
            strlen(path), 
            found ? "TRUE" : "FALSE"
        );

        for (int i = 0; i < BYTE; i++)
        {
            node_trace[i] = -1;
        }
    } else {
        printf("\n<%c> Not Found.\n\n", (char) c);
    }

    return path;
}

void _find_bincode(NODE *node, int c, int* path, int *found)
{
    int i = 0;

    if (node->value == c) 
    {
        *found = 1;
    }
    
    if (node->left != NULL && !(*found))
    {
        while (i < BYTE)
        {
            if (path[i] == -1) 
            {
                path[i] = 0;
                break;
            } else {
                i++;
            }
        }

        _find_bincode(node->left, c, path, found);

        if (!(*found)) 
        { 
            path[i] = -1;
        }
    }

    if (node->right != NULL && !(*found))
    {
        while(i < BYTE)
        {
            if (path[i] == -1) 
            {
                path[i] = 1;
                break;
            } else {
                i++;
            }
        }

        _find_bincode(node->right, c, path, found);

        if (!(*found)) 
        { 
            path[i] = -1;
        }
    }
}
