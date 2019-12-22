
#include "headers/skveez.h"
#include "headers/stack.h"

int main(int argc, char const *argv[])
{
	
	char* data = load_file("file.txt");
	// int* data = rnumg(1, 100, 20);
	Node* ptree = n_init(data[0]);

	for (int i = 1; i < f_size; ++i)
	{
		add(ptree, data[i]);
	}


  int path[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
  int found = 0;
  
  // BUG, FIX this
  find_bincode(ptree, 'b', path, &found);

  for (size_t i = 0; i < 8; i++)
  {
      printf("%d ", path[i]);
  }

  printf("\nfound = %d\n", found);

	STACK *s = new_STACK(3);
	push(s, 1);
	push(s, 2);
	push(s, 3);

	printf("%d\n", pop(s));
	printf("%d\n", pop(s));
	printf("%d\n", pop(s));

	// parse_r(ptree);
    // bin_code(data);
	return 0;
}









