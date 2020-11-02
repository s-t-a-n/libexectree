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

static t_gram_token		*gramgen_token_create_multikey(	t_gram_rule_type type,
														void *sig)
{
	static t_gram_token	*token;
	t_gram_token		*subtoken;

	if (sig == NULL)
	{
		token = NULL;
		return (NULL);
	}
	if (token || (token = ft_calloc(sizeof(t_gram_token), 1)))
	{
		if (!token->sig && !vector(&token->sig, V_CREATE, VEC_DEF_SIZE, NULL))
			return (NULL);
		if ((subtoken = gramgen_token_create(type/2, sig)))
		{
			if (vector(&token->sig, V_PUSHBACK, 0, subtoken))
				return (token);
		}
	}
	return (NULL);
}

t_gram_token		*gramgen_token_create(t_gram_rule_type type, void *sig)
{
	t_gram_token	*token;

	if (type & (NONTERMINAL_MULT|UNBOUND_NONTERMINAL_MULT))
		return (gramgen_token_create_multikey(type, sig));
	else if (sig == NULL)
		return (NULL);
	token = malloc(sizeof(t_gram_token));
	if (token)
	{
		token->type = type;
		token->sig = sig;
	}
	return (token);
}

t_gram_token		*gramgen_token_destroy(t_gram_token *token)
{
	if (token)
	{
		if (token->sig && token->type & (NONTERMINAL_MULT|UNBOUND_NONTERMINAL_MULT))
		{
			while (*(size_t *)vector(&token->sig, V_SIZE, 0, NULL) > 0)
			{
				gramgen_token_destroy(vector(&token->sig, V_PEEKBACK, 0, NULL));
				vector(&token->sig, V_POPBACK, 0, NULL);
			}
			vector(&token->sig, V_DESTROY, false, NULL);
		}
		else if (token->type & (TERMINAL|UNBOUND_NONTERMINAL))
		{
			free(token->sig);
		}
	}
	free(token);
	return (NULL);
}
