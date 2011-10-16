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

#ifndef _LIBCAVL_H_
#define _LIBCAVL_H_

struct treenode {
	void		*elem;		/* element */
	struct treenode	*left, *right;	/* node's children pointer */
};

struct tree {
	/* root node pointer */
	struct treenode	*root;
	/* function used to compare nodes */
	int		 (*n_cmp)(void *elem1, void *elem2);
	/* function used post node deletion */
	int		 (*n_del)(void *elem);
	/* iterator callback used in the iterator function */
	int		 (*n_itr)(void *elem, void *ctx);
	/* status storage variable */
	int		 err;
};

/* Creates a new tree and initialize its structure */
struct tree	*new_tree(void);
/* Add node and balance it */
int		 tree_addnode(struct tree *, void *);
/* Search for value in tree using compare function */
struct treenode *tree_search(struct tree *, void *);
/* Deletes specified node from the tree and balance it */
int		 tree_delnode(struct tree *, void *);
/* returns tree height */
int		 tree_height(struct tree *);
/* returns treenode height */
int		 treenode_height(struct treenode *);
/* uses n_itr callback while iterating through all nodes */
int		 tree_iterate(struct tree *, void *);
/* returns error string */
const char	*tree_strerror(struct tree *);
/* deletes all nodes, calling node deletion callback on each node
 * and deletes the tree structure
 */
int		 tree_delete(struct tree *);

/* get treenode element */
#define TREENODE_DATA(node) (node)->elem
/* get error number */
#define TREE_ERRNO(tree) (tree)->err

/* Deletion function and iterator function must return
 * 0 on success, else operations will abort */
/* sets comparation function */
#define TREE_COMPARE_FUNC(tree, function) (tree)->n_cmp = function
/* sets node deletion handling function */
#define TREE_DELETION_FUNC(tree, function) (tree)->n_del = function
/* sets node iteration callback */
#define TREE_ITERATOR_FUNC(tree, function) (tree)->n_itr = function

/* return statuses for reference */
enum return_status {
	TNOERROR,		/* OK */
	TWDUPLICATEDVALUE,	/* duplicated node */
	TEMALLOC,		/* no memory left */
	TENULLNODE,		/* function expected non null node */
	TEEMPTYTREE,		/* there are no root nodes */
	TENOTFOUND,		/* node not found */
	TEUSERCALLBACK,		/* user callback returned error */
	TEMISSINGCALLBACK,	/* no callback defined */
};

#endif /* _LIBCAVL_H_ */
