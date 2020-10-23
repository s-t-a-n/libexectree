/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_parse.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 21:50:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/22 22:35:23 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

void	*exectree_parse(void *_tree, const char *str)
{
	t_exectree *tree;

	tree = (t_exectree *)_tree;

	// call lexer -> build concrete syntax tree
	// call parser -> build abstract syntax tree out of string and concrete syntax tree
	return (tree);
	(void)str; // STUB
}
