/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:14 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 22:40:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

#include "lexergenerator.h"

t_lex_node			*lexer_find_node(t_lexer_ir *ir, char *key)
{
	t_lex_node		*node;
	size_t			i;

	i = *(size_t *)vector(&ir->nodes, V_SIZE, 0, NULL);
	while (i > 0)
	{
		node = vector(&ir->nodes, V_PEEKAT, i - 1, NULL);
		if (ft_strcmp(node->nonterminal, key) == 0)
			return (node);
		i--;
	}
	return (NULL);
}
