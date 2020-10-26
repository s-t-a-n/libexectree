/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   definition_lifetime.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:34 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:27:33 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "grammargenerator.h"

t_gram_definition	*gramgen_definition_create(void)
{
	t_gram_definition *def;

	def = malloc(sizeof(t_gram_definition));
	if (def)
	{
		if (!vector(&def->tokens, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(def);
			return (NULL);
		}
	}
	return (def);
}

t_gram_definition	*gramgen_definition_destroy(t_gram_definition *def)
{
	if (def)
	{
		while (*(size_t *)vector(&def->tokens, V_SIZE, 0, NULL) > 0)
		{
			gramgen_token_destroy(vector(&def->tokens, V_PEEKBACK, 0, NULL));
			vector(&def->tokens, V_POPBACK, 0, NULL);
		}
		vector(&def->tokens, V_DESTROY, 0, NULL);
	}
	free(def);
	return (NULL);
}
