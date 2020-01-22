#include "../headers/util.h"
#include "../headers/tree.h"
#include "../headers/stack.h"
#include "../headers/skveez.h"

const unsigned int BYTE = 8;
int f_size = 0, MAX_CMPD_SIZE = 0;

void skveez(const char* data, const char* d)
{
    char* raw_data = load_file(data);

    f_size = (int)strlen(raw_data);
    if (!f_size) exit(1);
    MAX_CMPD_SIZE = ((f_size) / 2) + 1; 

    NODE* char_tree = optimised_tree(raw_data, f_size);

    char codes[f_size][BYTE/2];
    char out_data[MAX_CMPD_SIZE];
    const char* comp_data = (char*) &out_data;

    for (int i = 0; i < f_size; ++i)
    {
        char* sc = find_bincode(char_tree, raw_data[i]);
        strcpy(codes[i], sc);
        free(sc);
    }


    const int loops = f_size % 2 == 0 ? f_size : f_size - 1;

    for (int i = 0; i <= loops; i += 2)
    {
        char* pair_code = malloc(sizeof(char) * (BYTE + 1));
        strcpy(pair_code, codes[i]);
        strcat(pair_code, codes[i + 1]);
        pair_code[BYTE] = '\0';

        int ascii_code = bin_to_decimal(pair_code);

        if (ascii_code <= 32) ascii_code += 32 * 2;

        out_data[i/2] = ascii_code;

        free(pair_code);
		
    }
	
	NODE* name = new_NODE



    // out_data[MAX_CMPD_SIZE] = '\0';

    write_file("cmpd.txt", comp_data);

    char* compressed_data = load_file(d);

    double raw_size = (double) strlen(raw_data);
    double cmpd_size = (double) strlen(compressed_data);
    double rate = (raw_size - cmpd_size) / raw_size * 100;

    printf("Original Size: %.0f\n", raw_size);
    printf("Compressed Size: %.0f\n", cmpd_size);
    printf("Compression Rate: %0.5f %%.\n", rate);

    printf("\n%p\n", char_tree);
    printf("%p\n", raw_data);
    printf("%p\n", compressed_data);

    // dis_NODE(char_tree);
    // free(raw_data);
    free(compressed_data);

    puts("\nEND!");
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

// this function require the given type for paramaters
// it can be casted however inside the function
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
    
    int* unq_ascii_codes = to_set(ascii_codes, size);
    int set_size = 0;
    
    for (int i = 0; i < size; ++i)
    {
        set_size += (unq_ascii_codes[i] != -1 && unq_ascii_codes[i] < 128) ? 1 : 0;
    }

    STACK* qs = new_STACK(set_size);
    create_quartiles(unq_ascii_codes, set_size, qs);
    STACK* quartiles = flipped(qs);
    NODE* opt_tree = new_NODE(pop(quartiles));

    for (int i = 1; i < set_size; ++i)
    {
        add(opt_tree, pop(quartiles));
    }

    free(unq_ascii_codes);
    dis_STACK(qs);
    dis_STACK(quartiles);

    return opt_tree;
}


char* find_bincode(NODE* node, int c)
{
    int found = 0;
    int node_trace[BYTE] = {-1, -1, -1, -1, -1, -1, -1, -1};
    // char path[(BYTE/2) + 1] = "";
    // char* ptr = (char*) &path;

    char* path = malloc(((BYTE/2)+1) * sizeof(char));

    _find_bincode(node, c, node_trace, &found);

    if (found) {
        // char raw_path[BYTE] = "";
        // char* raw_code;
        int last_index = 0; // this variable might not be necessery
        for (int i = 0; i < BYTE; ++i)
        {
            if (node_trace[i] == 1) {
                strcat(path, "1");
                last_index++;
            } else if (node_trace[i] == 0) {
                strcat(path, "0");
                last_index++;
            }
        }

        path[last_index] = '\0';


        // printf("Character: %c | Skveez Code: %s | Length: %lu | Found: %s\n\n", 
        //     (char) c, 
        //     path, 
        //     strlen(path), 
        //     found ? "TRUE" : "FALSE"
        // );


        for (size_t i = 0; i < BYTE; i++)
        {
            node_trace[i] = -1;
        }
    } else {
        printf("\n<%c> Not Found.\n\n", (char) c);
    }

    return path;
}

void _find_bincode(NODE *NODE, int c, int* path, int *found)
{
    int i = 0;

    if (NODE->value == c) *found = 1;

    if (NODE->left != NULL && !(*found))
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

        _find_bincode(NODE->left, c, path, found);

        if (!(*found)) path[i] = -1;
    }

    if (NODE->right != NULL && !(*found))
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

        _find_bincode(NODE->right, c, path, found);

        if (!(*found)) path[i] = -1;
    }
}

