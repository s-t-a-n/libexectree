/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:46:48 by sverschu      #+#    #+#                 */
/*   Updated: 2020/08/28 20:03:22 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_tree		*tree_new(void)
{
	t_tree *tree;

	tree = ft_calloc(sizeof(t_tree), 1);
	if (tree)
	{
	}
	return (tree);
}

t_tree		*tree_destroy(t_tree *tree)
{
	t_node	*node;

	node = tree->root;
	while (node->neighbour)
	{
		branch_destroy(node);
		node = node->neighbour;
	}
	free(tree);
	return (NULL);
}
