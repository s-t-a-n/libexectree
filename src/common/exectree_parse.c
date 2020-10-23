/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_parse.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 21:50:42 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/23 19:14:59 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "exectree_internal.h"

void	*exectree_parse(void *_tree, const char *str)
{
	t_exectree *tree;

	tree = (t_exectree *)_tree;

	// call lexer -> build concrete syntax tree
	tree->lex_tree = lexer(tree, str);

	// call parser -> build abstract syntax tree out of string and concrete syntax tree
	return (tree);
	(void)str; // STUB
}
