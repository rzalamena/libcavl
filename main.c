#include <stdio.h>
#include <stdlib.h>

#include "libcavl.h"

/* Print functions aren't provided with the libcavl,
 * because they are not generic enough to be there.
 * Anyway they would be only usefull for debugging.
 */

static void
treenode_print(struct treenode *n)
{
	int	*tmp;

	if (NULL == n)
		return;

	tmp = TREENODE_DATA(n);

	if (n->left != NULL)
		treenode_print(n->left);
	printf(" %d", *tmp);
	if (n->right != NULL)
		treenode_print(n->right);
}

static void
treenode_print_alt(struct treenode *n, unsigned int h)
{
	unsigned int	 counter;
	int		*tmp;

	if (NULL == n) {
		for (counter = 0; counter < h; counter++) {
			printf("\t");
		}
		printf("*\n");
		return;
	}
	tmp = TREENODE_DATA(n);

	treenode_print_alt(n->right, (h + 1));
	for (counter = 0; counter < h; counter++) {
		printf("\t");
	}
	printf("%d\n", *tmp);

	treenode_print_alt(n->left, (h + 1));
}

static void
tree_print(struct tree *t)
{
	treenode_print_alt(t->root, 0);
	treenode_print(t->root);
}

int
main(int argc, char *argv[])
{
	printf("C AVL example program\n");

	struct tree	*t;
	int		 data2, data3, data4;
	int		 data;
	data = 5; data2 = 2; data3 = 9; data4 = 99999;

	t = new_tree();
	/* In real world application you wouldn't be using
	 * like this, instead you should use pointers to your
	 * application data type and allocate it dynamically
	 */
	tree_addnode(t, &data);
	tree_addnode(t, &data2);
	tree_addnode(t, &data3);
	tree_addnode(t, &data4);

	printf("\n");
	tree_print(t);
	printf("\nHeight == %d\n", tree_height(t));

	return 0;
}
