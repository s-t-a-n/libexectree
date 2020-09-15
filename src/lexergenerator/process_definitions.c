/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_process_definitions.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 17:44:39 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/15 22:33:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "lexergenerator.h"

static t_lex_node		*find_lex_node(t_lexer_ir *ir, char *key)
{
	t_lex_node		*node;
	size_t				i;

	i = *(size_t *)vector(&ir->nodes, V_SIZE, 0, NULL);
	while (i > 0)
	{
		node = vector(&ir->nodes, V_PEEKAT, i - 1, NULL);
		if (ft_strcmp(node->nonterminal, key) == 0)
			return(node);
		i--;
	}
	// if no candidate was found, push the required node to a post fix vector so we
	// can add the candidate later, or return error
	return (NULL);
}

static uint8_t			process_nonterminal(t_lex_node *node, t_lex_definition *def, t_lexer_ir *ir, char **line)
{
	t_lex_token			*token;
	char				*key;
	size_t				keylen;

	(*line)++;
	keylen = ft_strclen(*line, '>');
	key = ft_strsub(*line, 0, keylen);
	if (key)
	{
		token = ft_strcmp(node->nonterminal, key) == 0 ?
				lexer_token_create(NONTERMINAL, node) : 
				lexer_token_create(NONTERMINAL, find_lex_node(ir, key));
		if (token)
		{
			logger(INFO, 3, "lexer_generator", "adding nonterminal to definition", key);
			vector(&def->tokens, V_PUSHBACK, 0, token);
		}
		else
		{
			logger(WARN, 3, "lexer_generator", "can't find nonterminal for key", key);
			// add to post stack here
		}
		free(key);
	}
	else
		return(0);
	return (1);
}

static uint8_t			process_literal(t_lex_definition *def, char **line)
{
	t_lex_token			*token;
	char				*word;
	size_t				wordlen;

	(*line)++;
	wordlen = 0;
	while(*(*line + wordlen) != '\'' || *(*line + wordlen - 1) == '\\')
		wordlen++;
	word = ft_strsub(*line, 0, wordlen);
	(*line) += wordlen + (*(*line + wordlen) ? 1 : 0);
	if (word)
	{
		token = lexer_token_create(TERMINAL, word);
		if (!(token && vector(&def->tokens, V_PUSHBACK, 0, token)))
		{
			free(token);
			free(word);
			return (0);
		}
		else
			logger(INFO, 3, "lexer_generator", "adding (literal) terminal to definition", word);
	}
	return (1);
}

static uint8_t			process_word(t_lex_definition *def, char **line)
{
	t_lex_token			*token;
	char				*word;
	size_t				wordlen;

	wordlen = 0;
	while(ft_isalnum(*(*line + wordlen)))
		wordlen++;
	word = ft_strsub(*line, 0, wordlen);
	(*line) += wordlen + (*(*line + wordlen) ? 1 : 0);
	if (word)
	{
		logger(INFO, 3, "lexer_generator", "adding (word) terminal to definition", word);
		token = lexer_token_create(TERMINAL, word);
		if (def)
			vector(&def->tokens, V_PUSHBACK, 0, token);
		else
		{
			free(word);
			return (0);
		}
	}
	return (1);
}

uint8_t					process_definitions(t_lexer_ir *ir,
											t_lex_node *node,
											char **line)
{
	t_lex_definition	*def;

	*line = ft_strscan(*line);
	if (**line == '|' || **line == '=')
	{
		def = lexer_definition_create();
		if (def)
		{
			(*line)++;
			*line = ft_strscan(*line);
			while(**line)
			{
				// right now this just dumps everything seperately : definitions should be self contained -> read untill '|' 
				if (**line == '\'')
					process_literal(def, line);
				else if (**line == '<')
					process_nonterminal(node, def, ir, line);
				else if (ft_isalnum(**line))
					process_word(def, line);
				*line = ft_strscan(*line);
			}
			vector(&node->definitions, V_PUSHBACK, 0, def);
		}
		else
			return (0);
	}
	else
		logger(WARN, 3, "lexer_generator", "Line doesn't start with '|' or '='", *line);
	return (1);
}
