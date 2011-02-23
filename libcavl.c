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

#include <stdlib.h>

#include "libcavl.h"

/* prototypes */
static int	 tree_balance(struct tree *);
struct treenode	*treenode_balance(struct treenode *);
static struct treenode *tree_balance_rec(struct treenode *);


static int
default_cmp(void *n1, void *n2)
{
	return (n1 < n2) ? -1 :
	    (n1 > n2) ? 1 : 0;
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

struct treenode *
tree_search(struct tree *t, void *e)
{
	struct treenode	*aux;
	int		 res;

	if (NULL == t->root)
		return NULL;
	
	aux = t->root;
	do {
		res = t->n_cmp(aux->elem, e);
		if (res == 0)
			return aux;
		else if (res > 0) {
			if (aux->left != NULL)
				aux = aux->left;
			else
				return NULL;
		} else {
			if (aux->right != NULL)
				aux = aux->left;
			else
				return NULL;
		}
	} while (aux->left != NULL || aux->right != NULL);
	return NULL;
}

int
tree_addnode(struct tree *t, void *e)
{
	int status = SUCCESS;

	if (NULL == t)
		return ENULLTREE;

	if ((status = tree_justaddnode(t, e)) != SUCCESS)
		return status;

	if ((status = tree_balance(t)) != SUCCESS)
		return status;

	return status;
}

int
tree_justaddnode(struct tree *t, void *e)
{
	struct treenode		*n, *helper;

	if (NULL == t)
		return ENULLTREE;

	n = malloc(sizeof(struct treenode));
	if (NULL == n)
		return EMALLOC;

	/* initialize the node to avoid trash */
	n->elem = e;
	n->right = NULL;
	n->left = NULL;

	if (NULL == t->root) {
		t->root = n;
		return SUCCESS;
	}

	if (NULL == t->n_cmp)
		t->n_cmp = default_cmp;

	helper = t->root;
	while (helper != NULL) {
		if (t->n_cmp(helper->elem, n->elem) > 0) {
			if (helper->left != NULL) {
				helper = helper->left;
			} else {
				helper->left = n;
				break;
			}
		} else if (t->n_cmp(helper->elem, n->elem) < 0) {
			if (helper->right != NULL) {
				helper = helper->right;
			} else {
				helper->right = n;
				break;
			}
		} else {
			free(n);
			/* usually its not allowed repeated elements
			 * so lets just ignore it and play safe */
			return WDUPLICATEDVALUE;
		}
	}
	return SUCCESS;
}

int
tree_delnode(struct tree *t, struct treenode *n)
{
	if (NULL == t || NULL == n)
		return ENULLTREE | ENULLNODE;

	/* TODO See if we can try to free node content
	 * Remove node, try to balance it
	 */
	return ETODO;
}

int
tree_height(struct tree *t)
{
	if (NULL == t || NULL == t->root)
		return ENULLTREE | ENULLNODE;

	return treenode_height(t->root);
}

static int
tree_balance(struct tree *t)
{
	if (NULL == t)
		return ENULLTREE;

	if (t->root != NULL) {
		t->root = tree_balance_rec(t->root);
	} else
		return ENULLNODE;

	return SUCCESS;
}

static struct treenode *
tree_balance_rec(struct treenode *n)
{
	if (n == NULL)
		return NULL;

	if (n->left != NULL)
		n->left = tree_balance_rec(n->left);
	if (n->right != NULL)
		n->right = tree_balance_rec(n->right);

	return treenode_balance(n);
}

int
treenode_height(struct treenode *n)
{
	unsigned int left, right;
	left = right = 0;

	if (NULL == n)
		return 0;

	if (n->left != NULL)
		left = treenode_height(n->left);
	if (n->right != NULL)
		right = treenode_height(n->right);

	return (left > right) ? ++left : ++right;
}

static struct treenode *
treenode_rotateleft(struct treenode *n)
{
	struct treenode	*t = n->right;
	n->right = t->left;
	t->left = n;
	return t;
}

static struct treenode *
treenode_rotateright(struct treenode *n)
{
	struct treenode *t = n->left;
	n->left = t->right;
	t->right = n;
	return t;
}

static struct treenode *
treenode_doublerotateleft(struct treenode *n)
{
	n = treenode_rotateright(n->right);
	return treenode_rotateleft(n);
}

static struct treenode *
treenode_doublerotateright(struct treenode *n)
{
	n = treenode_rotateleft(n->left);
	return treenode_rotateright(n);
}

struct treenode *
treenode_balance(struct treenode *n)
{
	if (NULL == n)
		return NULL;

	int	 right = treenode_height(n->right),
	    left = treenode_height(n->left);

	if (left - right > 1) {
		if (treenode_height(n->left->right)
		    - treenode_height(n->left->left) > 1)
			return treenode_doublerotateright(n);
		else
			return treenode_rotateright(n);
	} else if (right - left > 1) {
		if (treenode_height(n->right->left)
		    - treenode_height(n->right->right) > 1)
			return treenode_doublerotateleft(n);
		else
			return treenode_rotateleft(n);
	}
	return n;
}
