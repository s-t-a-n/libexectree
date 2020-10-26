/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grammar_ir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:46:09 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG
# include <assert.h>
#endif

#include "libft.h"
#include "get_next_line.h"

#include "logger.h"
#include "grammargenerator.h"

/*
** simple top-down parser for extracting grammar rules from a BNF
** file. excuse the mess; 42 requires 'norminette' which is superrestrictive
** on function length (max 25 lines).
*/

static uint8_t	parse_line(t_grammar_ir *ir, char *line)
{
	static t_gram_node *node;

	if (!*line || *line == '#' || !*ft_strscan(line) || *ft_strscan(line) == '#')
		return (0);
	if (line[0] == '<')
	{
		line++;
		if (!(node = gramgen_process_new_production(ir, &line)))
			return (1);
	}
#ifdef DEBUG
	assert(node);
#endif
	return (gramgen_process_definitions(ir, node, &line));
}

t_grammar_ir		*grammar_ir_generate(const char *bnf_fpath)
{
	int			fd;
	t_grammar_ir	*ir;
	char		*line;

	if ((ir = grammar_ir_create()))
	{
		if ((fd = open(bnf_fpath, O_RDONLY)) >= 0)
		{
			while (get_next_line(fd, &line))
			{
				if (parse_line(ir, line) != 0)
				{
					free(line);
					close(fd);
					return (grammar_ir_destroy(ir));
				}
				free(line);
			}
			free(line);
			close(fd);
		}
		else
		{
			return (grammar_ir_destroy(ir));
		}
		if (gramgen_post_process(ir) != 0)
			return (grammar_ir_destroy(ir));
	}
	return (ir);
}
