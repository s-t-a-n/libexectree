/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 22:10:55 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "lexergenerator.h"

t_lex_node	*lexer_node_create(char *nonterminal)
{
	t_lex_node *node;

	node = ft_calloc(sizeof(t_lex_node), 1);
	if(node)
	{
		if(!vector(&node->definitions, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(node);
			return (NULL);
		}
		node->nonterminal = nonterminal;
	}
	return (node);
}

t_lex_node	*lexer_node_destroy(t_lex_node *node)
{
	if (node)
	{
		while(*(size_t *)vector(&node->definitions, V_SIZE, 0, NULL) > 0)
		{
			lexer_definition_destroy(vector(&node->definitions, V_PEEKBACK, 0, NULL));
			vector(&node->definitions, V_POPBACK, 0, NULL);
		}
		vector(&node->definitions, V_DESTROY, false, NULL);
		free(node->nonterminal);
	}
	free(node);
	return (NULL);
}
