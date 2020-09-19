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
#include "lexergenerator.h"

t_lex_token	*lexgen_token_create(t_lex_definition_type type, void *sig)
{
	t_lex_token *token;

	if (sig == NULL)
		return (NULL);
	token = malloc(sizeof(t_lex_token));
	if (token)
	{
		token->type = type;
		token->sig = sig;
	}
	return (token);
}

t_lex_token		*lexgen_token_destroy(t_lex_token *token)
{
	if (token
		&& (token->type == TERMINAL || token->type == UNKNOWN_NONTERMINAL))
	{
		free(token->sig);
	}
	free(token);
	return (NULL);
}
