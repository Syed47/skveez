
#include "../headers/util.h"

static const unsigned int BYTE = 8;

int get_fsize(FILE *f)
{
    int size = 0; // number of characters
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

void write_file(const char* fname, const char* data)
{
    FILE* f = fopen(fname, "w");

    if (f != NULL) {
        fputs(data, f);
        fclose(f);
        f = NULL;
    } else {
        exit(1);
    }
}

void append_file(const char* fname, const char* data)
{
    FILE* f = fopen(fname, "a");
    if (f == NULL)
    {
        printf("Error appending to file %s\n", fname);
        exit(EXIT_FAILURE);
    } else {
        fputs(data, f);
    }

    fclose(f);
    f = NULL;
}

char* load_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) exit(1);
    int size     = get_fsize(f);
    int bytes    = sizeof(char) * size;
    char* all    = malloc(bytes);
    char* buffer = malloc(bytes);

    while (fgets(buffer, size, f) != NULL)
    {
        strcat(all, buffer);
    }

    all[bytes] = '\0';
    free(buffer);
    fclose(f);
    f = NULL;
    return all;
}

char** read_file_lines(const char* path, int start, int end)
{
    int delta = end - start;
    FILE* f = fopen(path, "r");
    if (delta < 1) // need to read at least one line
    {
        printf("Invalid line number <%d>\n", delta);
        return NULL;
    } else if (f == NULL) {
        printf("Error reading the file <%s>.", path);
        exit(EXIT_FAILURE);
    }

    char** buffer = malloc(sizeof(char*) * delta);
    const unsigned int line_len = 256;

    for (int i = 0; i <= delta; ++i)
    {
        buffer[i] = malloc(sizeof(char) * line_len);
        fgets(buffer[i], line_len, f); // also reads the \n at the end
    }

    fclose(f);
    return buffer;
}


void write_bfile(const char* fname, const char* data, unsigned int size)
{
    FILE *f = fopen(fname,"wb");
    if (f != NULL)
        fwrite(data, size, 1, f);

    fclose(f);
    puts("Binary file written.");
}

char* read_bfile(const char* fname)
{
    #define MAX_SIZE 10
    char* buffer = (char*) malloc(MAX_SIZE);
    FILE *f = fopen(fname,"rb");
    if (f != NULL)
        fread(buffer, MAX_SIZE, 1, f);
    fclose(f);
    puts("Binary file read.");
    return buffer;
}

char* bin_to_char(const char* bincode)
{
    char c = bin_to_decimal(bincode);
    printf("C -> %c\n", c);
    char* p = &c;
    printf("P -> %s\n", p);

    return p;
}

int bin_to_decimal(const char* bincode)
{
    const int len = strlen(bincode);
    const char* binaries = "01";
    int decimal = 0;

    for (int i = 0; i < len; ++i)
    {
        if (strncmp(&bincode[i], &binaries[1], 1) == 0)
        {
            decimal += ((int) pow(2, len - (i + 1)));
        }
    }

    return decimal;
}

int* rnumg(int from, int to, int smpl)
{
    int* nums = malloc(sizeof(from) * smpl);
    srand(time(NULL));
    int r;

    for (int i = 0; i < smpl; ++i)
    {
        r = (rand() % to) + from;
        nums[i] = r;
    }

    return nums;
}

int* array_to_set(const int* n, const int size)
{
    int *un = malloc(size * sizeof(int)); // free this
    for (size_t i = 0; i < size; i++) 
    {
        un[i] = -1; // ASCIIs are above 0, to 127
    }

    int index = 0;
    for (size_t i = 0; i < size; i++)
    {
        int streak = 0, flag = 0;
        for (size_t j = i+1; j <= size; j++)
        {
            if (n[i] == n[j] ) {
                streak++; 
            } else {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            un[index] = n[i];
            index++;
            i += streak;
        }

    }

    return un;
}

void printcc(char *arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%c : %d\n", arr[i], ((int)arr[i]));
    }
}

int* int_bincode(int num)
{
    int* bins = calloc(BYTE, sizeof(int)); 
    int index = 0;

    int den = num;

    while (den > 0)
    {
        int mod = den % 2;
        bins[index] = mod;
        den /= 2;
        index++;
    }

    for (int i = 0; i <= (BYTE/2); ++i)
    {
        int temp = bins[i];
        bins[i] = bins[((BYTE - 1) - i)];
        bins[((BYTE - 1) - i)] = temp;
    }

    return bins;
}


void bin_code(const char* str)
{
    int len = strlen(str);
    int bins[BYTE]; 
    for (int i = 0; i < len; ++i)
    {
        int index = 0;
        int den = (int)str[i];
        while (den > 0)
        {
            int mod = den % 2;
            bins[index] = mod;
            den /= 2;
            index++;
        }

        for (int i = BYTE - 1; i > -1; i--)
        {
            if (bins[i] == 0 || bins[i] == 1)
            {
                printf("%d", bins[i]);
            }
        }
        printf(" ");
    }
    printf("\n");
}
