/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 20:30:41 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 22:47:06 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"
#include "tree.h"

t_node		*tree_create()
{
	return (node_create());
}

t_node		*tree_destroy(t_node *root)
{
	if (root)
	{
		tree_destroy(root->left);
		tree_destroy(root->right);
		while (*(size_t *)vector(&root->children, V_SIZE, 0, NULL) > 0)
		{
			tree_destroy(vector(&root->children, V_PEEKBACK, 0, NULL));
			vector(&root->children, V_POPBACK, 0, NULL);
		}
		vector(&root->children, V_DESTROY, false, NULL);
		node_destroy(root);
	}
	return (NULL);
}
