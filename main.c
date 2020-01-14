
#include "headers/skveez.h"
#include "headers/stack.h"
#include "headers/map.h"
#include <string.h>

int main(int argc, char const *argv[])
{
	char* data = load_file("file.txt");
	// int* data = rnumg(1, 100, 20);
	Node* ptree = n_init((int)data[0]);
	printf("File size: %d | Data size: %lu\n", f_size, strlen(data));
	for (int i = 1; i < f_size; ++i)
	{
		add(ptree, (int)data[i]);
	}

    find_bincode(ptree, 'g');
	
    return 0;
}

