#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libcavl.h"

/* Numerical comparator used to order the tree */
static int
str_cmp(void *n1, void *n2)
{
	const char *na = n1, *nb = n2;
	return (strcmp(na, nb));
}

/* Print functions aren't provided with the libcavl,
 * because they are not generic enough to be there.
 * Anyway they would be only usefull for debugging.
 */

static void
treenode_print(struct treenode *n)
{
	const char	*tmp;

	if (NULL == n)
		return;

	tmp = TREENODE_DATA(n);

	if (n->left != NULL)
		treenode_print(n->left);
	printf(" %s", tmp);
	if (n->right != NULL)
		treenode_print(n->right);
}

static void
treenode_print_alt(struct treenode *n, unsigned int h)
{
	unsigned int	 counter;
	const char	*tmp;

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
	printf("%s\n", tmp);

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
	printf("C AVL example program\n"
	    "Enter something in stdin and enter a EOF\n");

	struct tree	*t;
	char		*aux;
	FILE		*ifp = stdin;

	/* create a new tree */
	t = new_tree();
	/* assign a compare function */
	TREE_COMPARE_FUNC(t, str_cmp);

	while (!feof(ifp)) {
		aux = malloc(64);
		aux[63] = '\0';
		fscanf(ifp, "%62s", aux);
		tree_addnode(t, aux);
	}

	printf("\n");
	tree_print(t);
	printf("\nHeight == %d\n", tree_height(t));

	return 0;
}
