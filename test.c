#include"stdio.h"
#include"./Structure File/interval_tree.h"
int main()
{
	interval_tree* tree = NULL;
	tree = insert_interval(tree, 100, 300);
	tree = insert_interval(tree, 900, 1000);
	tree=insert_interval(tree, 400, 500);
	
	printf("%d", is_overlapping(tree->root, 311, 400));
	int number_free_times=0;
	interval* free_times=find_free_times_interval(tree, 0, 1440, &number_free_times);
	print_intervals(free_times, number_free_times);
}
	