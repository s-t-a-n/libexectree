/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_ir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 22:10:46 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG
# include <assert.h>
#endif

#include "libft.h"
#include "get_next_line.h"

#include "logger.h"
#include "lexergenerator.h"

/*
** simple top-down parser for extracting grammar rules from a BNF
** file. excuse the mess; 42 requires 'norminette' which is superrestrictive
** on function length (max 25 lines).
*/ 

static uint8_t	parse_line(t_lexer_ir *ir, char *line)
{
	static t_lex_node *node;

	if (!*line || *line == '#')
		return (0);
	if (line[0] == '<')
	{
		line++;
		if (!(node = process_new_nonterminal(ir, &line)))
			return (1);
	}
#ifdef DEBUG
	assert(node);
#endif
	return(process_definitions(ir, node, &line));
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
				if (parse_line(ir, line) != 0)
				{
					free(line);
					close(fd);
					return(lexer_generator_destroy(ir));
				}
				free(line);
			}
			free(line);
			close(fd);
		}
		else
			return(lexer_generator_destroy(ir));
		if (lexer_post_process(ir) != 0)
			return(lexer_generator_destroy(ir));
	}
	return (ir);
}
