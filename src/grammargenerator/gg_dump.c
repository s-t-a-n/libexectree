/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:38 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:51:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** less restrained use of libraries since this is a mere debugging file
*/
#include <assert.h>
#include <stdio.h>

#include "vector.h"
#include "grammargenerator.h"

/*
void	gramgen_token_dump(t_gram_token *token)
{

}

void	gramgen_rule_dump(t_gram_rule *def)
{

}

void	gramgen_production_dump(t_gram_production *production)
{

}
*/

void	grammar_ir_dump(t_grammar_ir *ir)
{
	size_t				i, j, js, k, ks;
	t_gram_production			*production;
	t_gram_rule	*def;
	t_gram_token			*token;

	i = 0;
	while (i < ir->size)
	{
		production = vector(&ir->productions, V_PEEKAT, i, NULL);
		assert(production);
		printf("\n**** %s ****", production->nonterminal);
		js = *(size_t *)vector(&production->rules, V_SIZE, 0, NULL);
		j = 0;
		while (j < js)
		{
			printf("%s", "\n| ");
			def = vector(&production->rules, V_PEEKAT, j, NULL);
			assert(def);
			ks = *(size_t *)vector(&def->tokens, V_SIZE, 0, NULL);
			k = 0;
			while (k < ks)
			{
				token = vector(&def->tokens, V_PEEKAT, k, NULL);
				assert(token);
				if (token->type == TERMINAL)
					printf("%s ", token->terminal);
				else
					printf("[%s] ", ((t_gram_production *)token->production)->nonterminal);
				k++;
			}
			j++;
		}
		i++;
	}
}
