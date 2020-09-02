/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_populate.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 19:39:00 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 19:52:46 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

void	*exectree_populate(void *_tree, t_token *_token)
{
	t_tree *tree;
	tree = (t_tree *)_tree;
	return(tokentable_populate(tree->tokentable, _token));
}
