/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_nonterminal.c                              :+:    :+:            */
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

static t_gram_rule_type get_type(char **line)
{
	t_gram_rule_type type;

	if (**line == '<')
		type = ft_strcsetlen(*line, PRODUCTION_DELIMSET) < ft_strclen(*line, **line + 2)
				? NONTERMINAL_MULT : NONTERMINAL;
	else if (**line == '{')
		type = ft_strcsetlen(*line, PRODUCTION_DELIMSET) < ft_strclen(*line, **line + 2)
				? UNBOUND_NONTERMINAL_MULT : UNBOUND_NONTERMINAL;
	else if (**line == '[')
		type = RECURSIVE_NONTERMINAL;
	else
	{
		logger(WARN, 3, "process_nonterminal, get_type", "couldn't find type for rule", line);
		type = UNKNOWN;
	}
	(*line)++;
	return (type);
}

static t_gram_token	*create_token_for_key(	t_grammar_ir *ir,
											t_gram_rule_type type,
											char *key)
{
	t_gram_token				*token;
	t_gram_production			*production;

	production = grammar_ir_find_production(ir, key);
	if (production)
	{
		token = gramgen_token_create(type, production, NULL);
	}
	else
	{
		token = gramgen_token_create(type, NULL, ft_strdup(key));
		if (token && !lst_addback(&ir->post, token))
			return(gramgen_token_destroy(token));
	}
	return (token);
}

static uint8_t		push_token(t_gram_rule *rule, t_gram_token *token)
{
	if (vector(&rule->tokens, V_PUSHBACK, 0, token))
	{
		logger(INFO, 3, "grammar_generator", "adding nonterminal to rule");
		return (0);
	}
	return (1);
}

uint8_t				gg_process_nonterminal(	t_grammar_ir *ir,
											t_gram_rule *rule,
											char **line)
{
	t_gram_rule_type		type;
	t_gram_token			*token;
	char					*key;
	char					closechar;
	char					*excrement;

	closechar = **line + 2;
	type = get_type(line);
	key = ft_strtok(*line, PRODUCTION_DELIMSET);
	token = NULL;
	while (key)
	{
		if ((excrement = ft_strchr(key, closechar)))
			*excrement = '\0';
#ifdef DEBUG
		printf("multi-key is : |%s|\n", key);
#endif
		token = create_token_for_key(ir, type, key);
		free(key);
		key = ft_strtok(NULL, PRODUCTION_DELIMSET);
	}
	if (type & MULTI_RULETYPES)
		gramgen_token_create(type, NULL, NULL);
	*line += ft_strcsetlen(*line, PRODUCTION_CLOSESET);
	if (token && push_token(rule, token) == 0)
		return (0);
	gramgen_token_destroy(token);
	return (1);
}
