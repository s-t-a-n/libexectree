/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:08:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 22:39:51 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

#include "logging.h"
#include "lexer_generator.h"

/*
** simple recursive descent parser for extracting grammar rules from a BNF
** file. excuse the mess; 42 requires 'norminette' which is superrestrictive
** on function length (max 25 lines).
*/ 

static uint8_t	process_new_nonterminal(t_lexer_ir *ir, char **line)
{
	t_lex_object	*obj;
	size_t			keylen;

	obj = ft_calloc(sizeof(t_lex_object), 1);
	if (obj)
	{
		keylen = ft_strclen(*line, '>');
		obj->nonterminal = ft_strsub(*line, 0, keylen);
		*line += keylen + ft_strclen(*line, '=');
		if (obj->nonterminal)
		{
			logger(INFO, "Pushing", obj->nonterminal, NULL);
			vector(&ir->vec_lex_objects, V_PUSHBACK, 0, obj);
		}
		else
		{
			free(obj);
			return (0);
		}
	}
	return (1);
}

static uint8_t	process_options(t_lexer_ir *ir, char **line)
{
	(void)ir;
	(void)line;
	return (0);
}

static uint8_t	parse_line(t_lexer_ir *ir, char *line)
{
	if (!*line || *line == '#')
		return 1;
	if (line[0] == '<')
	{
		if (!process_new_nonterminal(ir, &line))
			return (0);
	}
	if (!process_options(ir, &line))
		return (0);
	else
		return (1);
}

t_lexer_ir		*lexer_generator(const char *bnf_fpath)
{
	int			fd;
	t_lexer_ir	*ir;
	char		*line;

	if ((ir = lexer_generator_create()))
	{
		if ((fd = open(bnf_fpath, O_RDONLY)) >= 0)
		{
			while(get_next_line(fd, &line))
			{
				if (!parse_line(ir, line))
				{
					free(line);
					close(fd);
					return(lexer_generator_destroy(ir));
				}
				free(line);
			}
			close(fd);
		}
		else
			return(lexer_generator_destroy(ir));
	}
	return (ir);
}
