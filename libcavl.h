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
	void		*elem; /* element */
	struct treenode	*left, *right; /* node's children pointer */
};

struct tree {
	struct treenode	*root; /* root node pointer */
	int		 (*n_cmp)(void *n1, void *n2);
	/* function used to compare nodes */
};

/* Creates a new tree and initialize its structure */
struct tree	*new_tree(void);
/* Add node and balance it */
int		 tree_addnode(struct tree *, void *);
/* just add nodes, usefull for batch add.
 * If you want to use it the tree properly later, call tree_balance */
int		 tree_justaddnode(struct tree *, void *);
/* Deletes specified node from the tree and balance it */
int		 tree_delnode(struct tree *, struct treenode *);
/* just remove node, usefull for batch removal,
 * Call tree_balance after using this */
int		 tree_justdelnode(struct tree *, struct treenode *);
/* returns tree height */
int		 tree_height(struct tree *);
/* returns treenode height */
int		 treenode_height(struct treenode *);

/* get treenode element */
#define TREENODE_DATA(node) (node)->elem
/* sets comparation function */
#define TREE_COMPARE_FUNC(tree, function) (tree)->n_cmp = function

/* return statuses for reference */
enum return_status {
	SUCCESS			= (0),
	WDUPLICATEDVALUE	= (1 << 0),
	ETODO			= (1 << 1),
	EMALLOC			= (1 << 2),
	ENULLTREE		= (1 << 3),
	ENULLNODE		= (1 << 4)
};

#endif /* _LIBCAVL_H_ */
