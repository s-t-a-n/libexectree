/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lifetime.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/15 22:14:09 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:40:46 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "grammargenerator.h"

static t_gram_token		*gramgen_token_create_multi(t_gram_rule_type type,
													t_gram_production *production,
													char *key)
{
	static t_gram_token	*token;
	t_gram_token		*subtoken;

	if (production == NULL && key == NULL)
	{
		token = NULL;
		return (NULL);
	}
	if (token || (token = ft_calloc(sizeof(t_gram_token), 1)))
	{
		token->type = type;
		if (!token->production && !vector(&token->production, V_CREATE, VEC_DEF_SIZE, NULL))
			return (NULL);
		if ((subtoken = gramgen_token_create(type/2, production, key)))
		{
			if (vector(&token->production, V_PUSHBACK, 0, subtoken))
				return (token);
		}
	}
	return (NULL);
}

/*
** to create a multi production token, call gramgen_token_create multiple times and
** clear the static cache by calling a last time with production == NULL
*/

t_gram_token		*gramgen_token_create(	t_gram_rule_type type,
											t_gram_production *production,
											char *terminal)
{
	t_gram_token	*token;

	if (type & MULTI_RULETYPES)
		return (gramgen_token_create_multi(type, production, terminal));
	token = malloc(sizeof(t_gram_token));
	if (token)
	{
		token->type = type;
		token->production = production;
		token->terminal = terminal;
	}
	return (token);
}

t_gram_token		*gramgen_token_destroy(t_gram_token *token)
{
	if (token)
	{
		if (token->production && token->type & MULTI_RULETYPES)
		{
			while (*(size_t *)vector(&token->production, V_SIZE, 0, NULL) > 0)
			{
				gramgen_token_destroy(vector(&token->production, V_PEEKBACK, 0, NULL));
				vector(&token->production, V_POPBACK, 0, NULL);
			}
			vector(&token->production, V_DESTROY, FALSE, NULL);
		}
		free(token->terminal);
	}
	free(token);
	return (NULL);
}
