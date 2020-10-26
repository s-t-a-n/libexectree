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

t_gram_token	*gramgen_token_create(t_gram_definition_type type, void *sig)
{
	t_gram_token *token;

	if (sig == NULL)
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
	if (token
		&& (token->type == TERMINAL || token->type == UNKNOWN_NONTERMINAL))
	{
		free(token->sig);
	}
	free(token);
	return (NULL);
}
