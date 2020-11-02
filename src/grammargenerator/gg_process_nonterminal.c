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

static t_gram_token	*gen_token_single(	t_grammar_ir *ir,
								t_gram_production *production,
								char *key)
{
	t_gram_token				*token;

	if (ft_strcmp(production->nonterminal, key) == 0)
		token = gramgen_token_create(NONTERMINAL, production);
	else if ((production = grammar_ir_find_production(ir, key)))
		token = gramgen_token_create(NONTERMINAL, production);
	else if ((token = gramgen_token_create(NONTERMINAL, ft_strdup(key))))
		lst_addback(&ir->post, token);
	else
		token = NULL;
	return (token);
}

//static t_gram_token	*gen_token_multi(	t_grammar_ir *ir,
//								t_gram_production *production,
//								char *key)
//{
//	t_gram_token				*token;
//
//	if (ft_strcmp(production->nonterminal, key) == 0)
//		token = gramgen_token_create(NONTERMINAL, production);
//	else if ((production = grammar_ir_find_production(ir, key)))
//		token = gramgen_token_create(NONTERMINAL, production);
//	else if ((token = gramgen_token_create(NONTERMINAL, ft_strdup(key))))
//		lst_addback(&ir->post, token);
//	else
//		token = NULL;
//	return (token);
//}

/*
** type is already checked before call to gg_process_nonterminal
*/

static t_gram_rule_type get_type(char **line, char **d)
{
	t_gram_rule_type type;

	if (**line == '<')
	{
		*d = ">";
		type = ft_strcsetlen(*line, PRODUCTION_DELIMSET) < ft_strcsetlen(*line, *d)
				? NONTERMINAL_MULT : NONTERMINAL;
	}
	else if (**line == '{')
	{
		*d = "}";
		type = ft_strcsetlen(*line, PRODUCTION_DELIMSET) < ft_strcsetlen(*line, *d)
				? UNBOUND_NONTERMINAL_MULT : UNBOUND_NONTERMINAL;
	}
	else if (**line == '|')
	{
		*d = "|";
		type = RECURSIVE_NONTERMINAL;
	}
	else
	{
		logger(WARN, 3, "process_nonterminal, get_type", "couldn't find type for rule", line);
		*d = NULL;
		type = UNKNOWN;
	}
	(*line)++;
	return (type);
}

static uint8_t		add_token_for_key(	t_gram_production *production,
										t_gram_rule *def,
										t_grammar_ir *ir,
										char *key)
{
	t_gram_token	*token;

	token = gen_token_single(ir, production, key);
	if (token)
	{
		if (vector(&def->tokens, V_PUSHBACK, 0, token))
		{
			logger(INFO, production ? 3 : 4,
						"grammar_generator",
						"adding nonterminal to rule",
						key, production ? "" : "adding to Post!");
			return (0);
		}
	}
	gramgen_token_destroy(token);
	return (1);
}

uint8_t				gg_process_nonterminal(t_gram_production *production,
											t_gram_rule *def,
											t_grammar_ir *ir,
											char **line)
{
	t_gram_rule_type		type;
	char					*key;
	char					*excrement;
	char					*delimiter;

	type = get_type(line, &delimiter);
	// loop this using ft_strtok, and add multiple keys to token
	if (ft_strcsetlen(*line, PRODUCTION_DELIMSET) < ft_strcsetlen(*line, PRODUCTION_CLOSESET))
	{
		// multi key
		key = ft_strtok(*line, PRODUCTION_DELIMSET);
		while (key)
		{
			if ((excrement = ft_strstr(key, delimiter)))
				*excrement = '\0';
			printf("multi-key is : |%s|\n", key);

			// call to gen_token_multi with static var like strtok
			key = ft_strtok(NULL, PRODUCTION_DELIMSET);
		}
	}
	else
	{
		// single key
		key = ft_strtok(*line, PRODUCTION_DELIMSET);
		if ((excrement = ft_strstr(key, delimiter)))
			*excrement = '\0';
		printf("single-key is : |%s|\n", key);
	}

	// pivot this to single push of token -> make gen_token_for_key(or keys with array)
	if (add_token_for_key(production, def, ir, key) == 0)
	{
		free(key);
		return (0);
	}
	free(key);
	return (1);
}
