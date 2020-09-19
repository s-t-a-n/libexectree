/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:38 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 22:10:41 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** less restrained use of libraries since this is a mere debugging file
*/
#include <assert.h>
#include <stdio.h>

#include "vector.h"
#include "lexergenerator.h"

/*
void	lexer_token_dump(t_lex_token *token)
{

}

void	lexer_definition_dump(t_lex_definition *def)
{

}

void	lexer_node_dump(t_lex_node *node)
{

}
*/

void	lexer_generator_dump(t_lexer_ir *ir)
{
	size_t				i, j, js, k, ks;
	t_lex_node			*node;
	t_lex_definition	*def;
	t_lex_token			*token;

	i = 0;
	while (i < ir->size)
	{
		node = vector(&ir->nodes, V_PEEKAT, i, NULL);
		assert(node);
		printf("\n**** %s ****", node->nonterminal);
		js = *(size_t *)vector(&node->definitions, V_SIZE, 0, NULL);
		j = 0;
		while(j < js)
		{
			printf("%s", "\n| ");
			def = vector(&node->definitions, V_PEEKAT, j, NULL);
			assert(def);
			ks = *(size_t *)vector(&def->tokens, V_SIZE, 0, NULL);
			k = 0;
			while (k < ks)
			{
				token = vector(&def->tokens, V_PEEKAT, k, NULL);
				assert(token);
				if (token->type == TERMINAL)
				{
					printf("%s ", (char *)token->sig);
				}
				else
				{
					printf("[%s] ", (char *)((t_lex_node *)token->sig)->nonterminal);
				}
				k++;
			}
			j++;
		}
		i++;
	}
}
