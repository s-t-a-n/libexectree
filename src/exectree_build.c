/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_build.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:14:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 15:20:50 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

void	*exectree_build(void *_tree, const char *str)
{
	t_tree *tree;
	t_token *token;
	t_token *candidate;

	tree = (t_tree *)_tree;
	while (*str)
	{
		token = tree->tokentable->tokens[(unsigned char)*str];
		candidate = NULL;
		while (token)
		{
			if (ft_strncmp(str, token->symbol, token->symlen) == 0)
				candidate = token;
			token = token->next;
		}
		if (candidate)
			tree_populate(tree, candidate, &str);
		str++;
	}
	return (_tree);
}
