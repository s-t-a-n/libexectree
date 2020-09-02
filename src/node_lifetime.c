/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:46:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 19:56:51 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_node		*node_new(void)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	if (node)
	{
		node->children = (t_node *)vector(&node->children, V_CREATE,
							NODE_DEFAULT_CHILDREN, NULL);
		if (!node->children)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}

t_node		*node_destroy(t_node *node)
{
	vector(node->children, V_DESTROY, 0, NULL);
	free(node->subject);
	free(node);
	return (NULL);
}
