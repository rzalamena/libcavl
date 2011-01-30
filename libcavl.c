/*
 * Copyright (c) 2011 Rafael F. Zalamena <rzalamena@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>

#include "libcavl.h"

static int
default_cmp(void *n1, void *n2)
{
	return (n1 < n2) ? -1 : 1;
}

struct tree *
new_tree(void)
{
	struct tree	*t;

	t = malloc(sizeof(struct tree));
	if (NULL == t)
		return NULL;

	t->root = NULL;
	t->n_cmp = NULL;

	return t;
}

int
tree_addnode(struct tree *t, void *e)
{
	int status = 0;

	if (NULL == t)
		return -1;

	if ((status = tree_justaddnode(t, e)) != 0)
		return status;

	if ((status = tree_balance(t)) != 0)
		return status;

	return status;
}

int
tree_justaddnode(struct tree *t, void *e)
{
	struct treenode		*n, *helper;

	if (NULL == t)
		return -1;

	n = malloc(sizeof(struct treenode));
	if (NULL == n)
		return -1;

	/* initialize the node to avoid trash */
	n->elem = e;
	n->right = NULL;
	n->left = NULL;

	if (NULL == t->root) {
		t->root = n;
		return 0;
	}

	if (NULL == t->n_cmp)
		t->n_cmp = default_cmp;
	/* add node to tree in respecting order to minimize
	 * node balance impact, this only applies to justaddnode calls
	 */
	helper = t->root;
	while (helper != NULL) {
		if (t->n_cmp(helper->elem, n->elem) > 0) {
			if (helper->left != NULL) {
				helper = helper->left;
			} else {
				helper->left = n;
				break;
			}
		} else {
			if (helper->right != NULL) {
				helper = helper->right;
			} else {
				helper->right = n;
				break;
			}
		}
	}

	return 0;
}

int
tree_delnode(struct tree *t, struct treenode *n)
{
	if (NULL == t || NULL == n)
		return -1;

	/* TODO See if we can try to free node content
	 * Remove node, try to balance it
	 */
	return 1;
}

int
tree_height(struct tree *t)
{
	if (NULL == t || NULL == t->root)
		return -1;

	return treenode_height(t->root);
}

int
tree_balance(struct tree *t)
{
	if (NULL == t)
		return -1;

	if (t->root != NULL)
		return treenode_balance(t->root);
	else
		return -1;
}

int
treenode_height(struct treenode *n)
{
	unsigned int left, right;
	left = right = 0;

	if (NULL == n)
		return -1;

	if (n->left != NULL)
		left = treenode_height(n->left);
	if (n->right != NULL)
		right = treenode_height(n->right);

	return (left > right) ? ++left : ++right;
}

int
treenode_balance(struct treenode *n)
{
	if (NULL == n)
		return -1;

	/* TODO balance this specified node
	 * we need the tree node height to do this
	 * the algorithm says: -1, 0 and 1 are ok
	 * > 1 and < -1 means unbalanced tree
	 * 
	 * TODO add, check heights and balance tree.
	 * Benchmark it
	 */
	return 0;
}
