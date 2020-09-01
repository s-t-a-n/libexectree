/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_lifetime.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 19:39:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/01 19:39:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

void		*exectree_create()
{
	return((void *)tree_create());
}

void		*exectree_destroy(void *_tree)
{
	return((void *)tree_destroy((t_tree *)_tree));
}