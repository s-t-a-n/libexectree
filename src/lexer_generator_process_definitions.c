/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_process_definitions.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 17:44:39 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 19:51:55 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "lexer_generator.h"

static t_lex_object		*find_lex_obj(t_lexer_ir *ir, char *key)
{
	t_lex_object		*obj;
	size_t				i;

	i = *(size_t *)vector(&ir->vec_lex_objects, V_SIZE, 0, NULL);
	while (i > 0)
	{
		obj = vector(&ir->vec_lex_objects, V_PEEKAT, i - 1, NULL);
		printf("obj : %p, obj->nonterminal -> %p, key : %s, index %zu\n", obj, obj->nonterminal, key, i - 1);
		if (ft_strcmp(obj->nonterminal, key) == 0)
			return(obj);
		i--;
	}
	// if no candidate was found, push the required object to a post fix vector so we
	// can add the candidate later, or return error
	printf("returning NULL\n");
	return (NULL);
}

static uint8_t			process_nonterminal(t_lex_object *obj, t_lexer_ir *ir, char **line)
{
	t_lex_definition	*def;
	char				*key;
	size_t				keylen;

	(*line)++;
	keylen = ft_strclen(*line, '>');
	key = ft_strsub(*line, 0, keylen);
	//printf("key : |%s|\n", key);
	if (key)
	{
		if (ft_strcmp(obj->nonterminal, key) == 0)
			def = lexer_definition_create(NONTERMINAL, NULL, obj);
		else
			def = lexer_definition_create(NONTERMINAL, NULL, find_lex_obj(ir, key));
		if (def)
		{
			logger(INFO, 3, "lexer_generator", "adding nonterminal to definition", key);
			vector(&obj->definitions, V_PUSHBACK, 0, def);
		}
		else
			logger(WARN, 3, "lexer_generator", "can't find nonterminal for key", key);
		free(key);
	}
	else
		return(0);
	return (1);
}

static uint8_t			process_literal(t_lex_object *obj, char **line)
{
	t_lex_definition	*def;
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
		logger(INFO, 3, "lexer_generator", "adding (literal) terminal to definition", word);
		def = lexer_definition_create(TERMINAL, word, NULL);
		if (def)
			vector(&obj->definitions, V_PUSHBACK, 0, def);
		else
		{
			free(word);
			return (0);
		}
	}
	return (1);
}

static uint8_t			process_word(t_lex_object *obj, char **line)
{
	t_lex_definition	*def;
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
		def = lexer_definition_create(TERMINAL, word, NULL);
		if (def)
			vector(&obj->definitions, V_PUSHBACK, 0, def);
		else
		{
			free(word);
			return (0);
		}
	}
	return (1);
}

uint8_t					process_definitions(t_lexer_ir *ir,
											t_lex_object *obj,
											char **line)
{
	*line = ft_strscan(*line);
	if (**line == '|' || **line == '=')
	{
		(*line)++;
		*line = ft_strscan(*line);
		while(**line)
		{
			if (**line == '\'')
				process_literal(obj, line);
			else if (**line == '<')
				process_nonterminal(obj, ir, line);
			else if (ft_isalnum(**line))
				process_word(obj, line);
			*line = ft_strscan(*line);
		}
	}
	else
		logger(WARN, 3, "lexer_generator", "Line doesn't start with '|' or '='", *line);
	return (1);
}
