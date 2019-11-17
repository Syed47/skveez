#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/*----------------------<TYPEDEFs>---------------------------*/
#define BYTE 8
typedef unsigned int byte;

typedef struct Node 
{
	int value;
	struct Node* left;
	struct Node* right;
} Node;

/*-----------------------<DECLARATION>---------------------------*/

static int f_size; // local to this file only
char* load_file(const char*);
int   get_fsize(FILE*);
void  printcc(char*, int);
void  bin_code(char*);
Node* n_init(int);
void  push(Node*, int);
void  parse_t(Node*);
int*  rnumg(int a, int b, int c);
/*-----------------------<DEFINITION>---------------------------*/

Node* n_init(int _val) 
{
	Node* r = malloc(sizeof(Node));
	r->left = NULL;
	r->right = NULL;
	r->value = _val;
	return r;
}	


void push(Node* root, int _val) 
{
	if (_val < root->value) {
		if (root->left == NULL) 
			root->left = n_init(_val);
		else
			push(root->left, _val);
  } else if (_val > root->value) {
	  if (root->right == NULL)
			root->right = n_init(_val);
	 	else
			push(root->right, _val);
  }
}

void parse_t(Node* node)
{
	if (node->left != NULL)
		parse_t(node->left);

	printf("%d\n", node->value);

	if (node->right != NULL)
		parse_t(node->right);
}

int* rnumg(int a, int b, int c)
{
	int* nums = malloc(sizeof(a) * c);
	srand(time(NULL));
	int r;

	for (int i = 0; i < c; ++i)
	{
		r = (rand() % b) + a;
		nums[i] = r;
	}

	return nums;
}




int get_fsize(FILE* f)
{
	int size = 0; // number of characters
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
}


char* load_file(const char* path) 
{
	FILE* f      = fopen(path, "r");
	int size     = get_fsize(f);
	int bytes    = sizeof(char) * size;
	char* all    = malloc(bytes);
	char* buffer = malloc(bytes);
	
	f_size = size;	

	if (f) 
		while(fgets(buffer, size, f) != NULL) 
			strcat(all, buffer);

	free(buffer);
	fclose(f);

	return all;
}



void printcc (char* arr, int len)
{
	for (int i = 0; i < len; ++i) 
	{
		printf("%c : %d\n", arr[i], ((int) arr[i]));
	}
}



/* 
	Seems to work fine for now but need to be more robust 
	and need to go through proper testing.
*/
void bin_code(char* str) 
{
	int len = strlen(str);
	int bins[BYTE] = {}; // Array for flipping remainders
	for(int i = 0; i < len; ++i)
	{
		int index = 0;
		int den = (int) str[i];
		while(den > 0)
		{
			int mod = den % 2;
			bins[index++] = mod;
			den /= 2;	
		}
		// Remainders need to be printed in reverse order
		for (int i = BYTE - 1; i > -1; i--) printf("%d", bins[i]);
		printf(" ");
	}

	printf("\nLENGTH %d\n", len);
}



/*-----------------------<MAIN>---------------------------*/

int main(int argc, char const *argv[])
{
	
	// char* data = load_file("file.txt");
	int* data = rnumg(1, 100, 20);
	Node* root = n_init(data[0]);

	for (int i = 1; i < 20; ++i)
	{
		push(root, data[i]);
	}

	parse_t(root);

	return 0;
}
