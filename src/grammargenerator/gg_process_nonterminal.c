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
								t_gram_node *node,
								char *key)
{
	t_gram_token				*token;

	if (ft_strcmp(node->nonterminal, key) == 0)
		token = gramgen_token_create(NONTERMINAL, node);
	else if ((node = grammar_ir_find_node(ir, key)))
		token = gramgen_token_create(NONTERMINAL, node);
	else if ((token = gramgen_token_create(NONTERMINAL, ft_strdup(key))))
		lst_addback(&ir->post, token);
	else
		token = NULL;
	return (token);
}

//static t_gram_token	*gen_token_multi(	t_grammar_ir *ir,
//								t_gram_node *node,
//								char *key)
//{
//	t_gram_token				*token;
//
//	if (ft_strcmp(node->nonterminal, key) == 0)
//		token = gramgen_token_create(NONTERMINAL, node);
//	else if ((node = grammar_ir_find_node(ir, key)))
//		token = gramgen_token_create(NONTERMINAL, node);
//	else if ((token = gramgen_token_create(NONTERMINAL, ft_strdup(key))))
//		lst_addback(&ir->post, token);
//	else
//		token = NULL;
//	return (token);
//}

/*
** type is already checked before call to gg_process_nonterminal
*/

static t_gram_definition_type get_type(char **line, char *d)
{
	t_gram_definition_type type;

	if (**line == '<')
	{
		*d = '>';
		if (ft_strclen(*line, ',') < ft_strclen(*line, *d))
			type = NONTERMINAL_MULT;
		else
			type = NONTERMINAL;
	}
	else if (**line == '{')
	{
		*d = '}';
		if (ft_strclen(*line, ',') < ft_strclen(*line, *d))
			type = UNBOUND_NONTERMINAL_MULT;
		else
			type = UNBOUND_NONTERMINAL;
	}
	else
	{
		logger(WARN, 3, "process_nonterminal, get_type", "couldn't find type for rule", line);
		type = UNKNOWN;
	}
	(*line)++;
	return (type);
}

uint8_t				gg_process_nonterminal(t_gram_node *node,
											t_gram_definition *def,
											t_grammar_ir *ir,
											char **line)
{
	t_gram_token			*token;
	t_gram_definition_type	type;
	char					*key;
	char					delimiter;
	size_t					keylen;

	type = get_type(line, &delimiter);
	// loop this, and add multiple keys to token
	keylen = ft_strclen(*line, delimiter);
	if ((key = ft_strsub(*line, 0, keylen)))
	{
		token = gen_token_single(ir, node, key);
		if (token)
		{
			if (vector(&def->tokens, V_PUSHBACK, 0, token))
			{
				logger(INFO, node ? 3 : 4,
							"grammar_generator",
							"adding nonterminal to definition",
							key, node ? "" : "adding to Post!");
				(*line) += keylen + (*(*line + keylen) ? 1 : 0);
				free(key);
				return (0);
			}
		}
		gramgen_token_destroy(token);
		free(key);
	}
	return (1);
}
