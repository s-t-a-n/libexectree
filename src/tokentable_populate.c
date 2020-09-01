/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokentable_populate.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 19:08:21 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/01 19:14:14 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_token		*tokentable_populate(t_tokentable *tokentable, t_token *_token)
{
	t_token	*token;

	if (tokentable->tokens[_token->symbol[0]])
	{
		token = tokentable->tokens[_token->symbol[0]];
		while (token->next)
			token = token->next;
		token->next = _token;
	}
	else
	{
		tokentable->tokens[_token->symbol[0]] = _token;
	}
	return (_token);
}
