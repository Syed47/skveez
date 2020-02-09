#include "headers/core.h"
#include "headers/util.h"
// #include <stdio.h>
// #include <stdlib.h>

int main(int argc, char const *argv[])
{

	skveez("./data/medium.txt", "./data/cmpd.txt");
 	unskveez("./data/cmpd.txt", "./data/dazzles.txt");

	// int* nums = rnumg(0, 100, 10);

	// NODE* t = new_NODE(nums[0]);

	// for (int i = 1; i < 10; ++i)
	// {
	// 	tree_add(t, nums[i]);
	// }

	// print_tree(t, 'd');

	return 0;
}
