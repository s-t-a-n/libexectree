/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_internal.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:38:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/08/28 20:04:24 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_INTERNAL_H
# define EXECTREE_INTERNAL_H

# include <stdlib.h>

# include "libft.h"

# include "vector.h"

# include "exectree.h"

typedef struct		s_node t_node;
typedef void		*t_vector;

typedef struct		s_node
{
	t_node			*parent;
	t_node			*neighbour;
	t_vector		children;
	void			(*solver)(t_node *node, unsigned int operator);
	unsigned int	operator;
	void			*subject;
}					t_node;

typedef struct		s_tree
{
	t_node			*root;
	size_t			cap;
	size_t			size;
}					t_tree;

t_node				*node_new();
t_node				*node_destroy(t_node *node);

t_node				*branch_destroy(t_node *root);

t_tree				*tree_new();
t_tree				*tree_destroy(t_tree *tree);

#endif
