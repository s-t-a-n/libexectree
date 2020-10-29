/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:14 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:40:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

#include "grammargenerator.h"

t_gram_production			*grammar_ir_find_production(t_grammar_ir *ir, char *key)
{
	t_gram_production		*production;
	size_t			i;

	i = *(size_t *)vector(&ir->productions, V_SIZE, 0, NULL);
	while (i > 0)
	{
		production = vector(&ir->productions, V_PEEKAT, i - 1, NULL);
		if (ft_strcmp(production->nonterminal, key) == 0)
			return (production);
		i--;
	}
	return (NULL);
}
