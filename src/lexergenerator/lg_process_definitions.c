/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_definitions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:03 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:53:07 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "lexergenerator.h"

static uint8_t			process_nonterminal(t_lex_node *node,
											t_lex_definition *def,
											t_lexer_ir *ir,
											char **line)
{
	t_lex_token			*token;
	char				*key;
	size_t				keylen;

	(*line)++;
	keylen = ft_strclen(*line, '>');
	if ((key = ft_strsub(*line, 0, keylen)))
	{
		if (ft_strcmp(node->nonterminal, key) == 0)
			token = lexgen_token_create(NONTERMINAL, node);
		else if ((node = lexer_ir_find_node(ir, key)))
			token = lexgen_token_create(NONTERMINAL, node);
		else if ((token = lexgen_token_create(UNKNOWN_NONTERMINAL, ft_strdup(key))))
			lst_addback(&ir->post, token);
		else
			token = NULL;
		if (token)
		{
			if (vector(&def->tokens, V_PUSHBACK, 0, token))
			{
				logger(INFO, node ? 3 : 4,
							"lexer_generator",
							"adding nonterminal to definition",
							key, node ? "" : "adding to Post!");
				(*line) += keylen + (*(*line + keylen) ? 1 : 0);
				free(key);
				return (0);
			}
		}
		lexgen_token_destroy(token);
		free(key);
	}
	return (1);
}

static uint8_t			process_literal(t_lex_definition *def, char **line)
{
	t_lex_token			*token;
	char				*word;
	size_t				wordlen;

	(*line)++;
	wordlen = 0;
	while (*(*line + wordlen) != '\'' || *(*line + wordlen - 1) == '\\')
		wordlen++;
	word = ft_strsub(*line, 0, wordlen);
	(*line) += wordlen + (*(*line + wordlen) ? 1 : 0);
	if (word)
	{
		token = lexgen_token_create(TERMINAL, word);
		if (token && vector(&def->tokens, V_PUSHBACK, 0, token))
		{
			logger(INFO, 3, "lexer_generator",
							"adding (literal) terminal to definition",
							word);
			return (0);
		}
		lexgen_token_destroy(token);
		free(word);
	}
	return (1);
}

static uint8_t			process_word(t_lex_definition *def, char **line)
{
	t_lex_token			*token;
	char				*word;
	size_t				wordlen;

	wordlen = 0;
	while (*(*line + wordlen) && (*(*line + wordlen) != ' ') && *(*line + wordlen) != '|')
		wordlen++;
	word = ft_strsub(*line, 0, wordlen);
	(*line) += wordlen + (*(*line + wordlen) ? 1 : 0);
	if (word)
	{
		token = lexgen_token_create(TERMINAL, word);
		if (token && vector(&def->tokens, V_PUSHBACK, 0, token))
		{
			logger(INFO, 3, "lexer_generator",
							"adding (word) terminal to definition",
							word);
			return (0);
		}
		free(word);
		lexgen_token_destroy(token);
	}
	return (1);
}

uint8_t					lexgen_process_definitions(t_lexer_ir *ir,
											t_lex_node *node,
											char **line)
{
	uint8_t				errors;
	t_lex_definition	*def;

	*line = ft_strscan(*line);
	errors = 0;
	if (**line == '|' || **line == '=')
	{
		def = lexgen_definition_create();
		if (def)
		{
			(*line)++;
			*line = ft_strscan(*line);
			while (**line)
			{
				if (**line == '\'')
					errors += process_literal(def, line);
				else if (**line == '<')
					errors += process_nonterminal(node, def, ir, line);
				else if (ft_isalnum(**line))
					errors += process_word(def, line);
				*line = ft_strscan(*line);
			}
			if (!vector(&node->definitions, V_PUSHBACK, 0, def))
				lexgen_definition_destroy(def);
		}
	}
	else
		logger(WARN, 3, "lexer_generator",
						"Line doesn't start with '|' or '='",
						*line);
	return (errors);
}
