#include"stdio.h"
#include"./Structure File/interval_tree.h"
int main()
{
	interval_tree* tree = NULL;
	tree = insert_interval(tree, 100, 300);
	insert_interval(tree, 400, 500);
	printf("%d", is_overlapping(tree->root, 311, 400));
}
	