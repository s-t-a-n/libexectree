/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lifetime.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/15 22:14:09 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/15 22:19:47 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "lexergenerator.h"

t_lex_token	*lexer_token_create(t_lex_definition_type type, void *sig)
{
	t_lex_token *token;

	token = malloc(sizeof(t_lex_token));
	if (token)
	{
		token->type = type;
		token->sig = sig;
	}
	return (token);
}

t_lex_token		*lexer_token_destroy(t_lex_token *token)
{
	if (token && token->type == TERMINAL)
	{
		free(token->sig);
	}
	free(token);
	return (NULL);
}
