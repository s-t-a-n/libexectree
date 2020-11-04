/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_terminal.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:03 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:15:20 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "grammargenerator.h"

static uint8_t		push_token(	t_gram_rule *rule,
								t_gram_token *token)
{
	if (token && vector(&rule->tokens, V_PUSHBACK, 0, token))
	{
		logger(INFO, 3, "grammar_generator",
						"adding (terminal) terminal to rule",
						token->terminal);
		return (0);
	}
	return (1);
}

uint8_t				gg_process_terminal(t_grammar_ir *ir,
										t_gram_rule *rule,
										t_gram_production *prod,
										char **line)
{
	t_gram_token	*token;
	char			closechar;
	char			*key;
	size_t			keylen;

	closechar = **line;
	keylen = ft_strstringlen(*line);
	(*line)++;
	key = ft_strsub(*line, 0, keylen);
	if (key)
	{
		token = gramgen_token_create(TERMINAL, prod, key);
		if (push_token(rule, token) == 0 && gramgen_lex_jtable_add(ir->lex_jtable, token))
		{
			(*line) += keylen + (*(*line + keylen) ? 1 : 0);
			return (0);
		}
		gramgen_token_destroy(token);
	}
	return (1);
}
