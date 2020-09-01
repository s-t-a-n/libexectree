/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:46:48 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/01 19:02:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_tree		*tree_new(size_t tokentable_size)
{
	t_tree *tree;

	tree = ft_calloc(sizeof(t_tree), 1);
	if (tree)
	{
		tree->tokentable = tokentable_create(tokentable_size);
		if (tree->tokentable)
		{
			free(tree);
			return (NULL);
		}
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
