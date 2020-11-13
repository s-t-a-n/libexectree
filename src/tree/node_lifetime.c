/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 16:38:46 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:31:02 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "vector.h"
#include "tree.h"

#define VEC_DEF_SIZE	12

t_node		*node_create()
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	if (node)
	{
		if (!vector(&node->children, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}

t_node		*node_destroy(t_node *node)
{
	if (node)
	{
		while (*(size_t *)vector(&node->children, V_SIZE, 0, NULL) > 0)
		{
			node_destroy(vector(&node->children, V_PEEKBACK, 0, NULL));
			vector(&node->children, V_POPBACK, 0, NULL);
		}
		vector(&node->children, V_DESTROY, FALSE, NULL);
		free(node->children);
	}
	free(node);
	return (NULL);
}
