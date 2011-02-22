#include <stdio.h>
#include <stdlib.h>

#include "libcavl.h"

/* Numerical comparator used to order the tree */
static int
num_cmp(void *n1, void *n2)
{
	int	*na = n1, *nb = n2;
	return (*na < *nb) ? -1 : 1;
}

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
	int		 data, data2, data3, data4, data5, data6;
	data = 5; data2 = 99; data3 = 9; data4 = 99999; data5 = 1; data6 = -1;

	/* create a new tree */
	t = new_tree();
	/* assign a compare function */
	TREE_COMPARE_FUNC(t, num_cmp);

	/* In real world application you wouldn't be using
	 * like this, instead you should use pointers to your
	 * application data type and allocate it dynamically
	 */
	tree_addnode(t, &data);
	tree_addnode(t, &data2);
	tree_addnode(t, &data3);
	tree_addnode(t, &data4);
	tree_addnode(t, &data5);
	tree_addnode(t, &data6);

	printf("\n");
	tree_print(t);
	printf("\nHeight == %d\n", tree_height(t));

	return 0;
}
