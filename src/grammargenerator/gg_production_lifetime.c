/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   production_lifetime.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:37:28 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"
#include "grammargenerator.h"

t_gram_production	*gramgen_production_create(char *nonterminal, t_gram_production_type type)
{
	t_gram_production *production;

	production = ft_calloc(sizeof(t_gram_production), 1);
	if (production)
	{
		if (!vector(&production->rules, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(production);
			return (NULL);
		}
		production->nonterminal = nonterminal;
		production->type = type;
	}
	return (production);
}

t_gram_production	*gramgen_production_destroy(t_gram_production *production)
{
	if (production)
	{
		while (*(size_t *)vector(&production->rules, V_SIZE, 0, NULL) > 0)
		{
			gramgen_rule_destroy(vector(&production->rules, V_PEEKBACK, 0,
																		NULL));
			vector(&production->rules, V_POPBACK, 0, NULL);
		}
		vector(&production->rules, V_DESTROY, FALSE, NULL);
		free(production->nonterminal);
	}
	free(production);
	return (NULL);
}
