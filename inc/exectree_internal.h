/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_internal.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:38:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/01 19:40:25 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_INTERNAL_H
# define EXECTREE_INTERNAL_H

# include <stdlib.h>

# include "libft.h"

# include "vector.h"
# include "exectree.h"

# define NODE_DEFAULT_CHILDREN 128

typedef struct		s_node t_node;
typedef void		*t_vector;

typedef struct		s_tokentable
{
	t_token			**tokens;
	unsigned int	size;
}					t_tokentable;

typedef struct		s_node
{
	t_node			*parent;
	t_vector		neighbour;
	t_vector		children;
	void			*(*solver)(void *subject, void *children, void *neighbours);
	unsigned int	operator;
	void			*subject;
}					t_node;

typedef struct		s_tree
{
	t_node			*root;
	size_t			cap;
	size_t			size;
	t_tokentable	*tokentable;
}					t_tree;

t_node				*node_new();
t_node				*node_destroy(t_node *node);

t_node				*branch_destroy(t_node *root);

t_tree				*tree_new(size_t tokentable_size);
t_tree				*tree_destroy(t_tree *tree);

t_tokentable		*tokentable_create(size_t _size);
t_token				*tokentable_populate(t_tokentable *tokentable, t_token *token);
t_tokentable		*tokentable_destroy(t_tokentable *tokentable);

#endif
