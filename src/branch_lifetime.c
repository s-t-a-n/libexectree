/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   branch_lifetime.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:57:39 by sverschu      #+#    #+#                 */
/*   Updated: 2020/08/28 21:46:52 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_node	*branch_destroy(t_node *root)
{
	while (*(size_t *)vector(&root->children, V_SIZE, 0, NULL) > 0)
	{
		branch_destroy(vector(&root->children, V_PEEKBACK, 0, NULL));
		vector(&root->children, V_POPBACK, 0, NULL);
	}
	vector(&root->children, V_DESTROY, false, NULL);
	free(root);
	return (NULL);
}
