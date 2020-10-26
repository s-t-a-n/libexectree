/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_definitions.c                              :+:    :+:            */
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

static void				*add_to_jtable(	t_grammar_ir *ir,
										t_gram_node *node,
										char *line)
{
	int					c;

	if (*line == '\'')
		c = *(line + 1);
	else if (ft_isalnum(*line) || *line == '_')
		c = *line;
	else
		return ("NULL'ISH");
	return (lst_addback(&ir->jtable[c], node));
}

uint8_t					gramgen_process_definitions(t_grammar_ir *ir,
											t_gram_node *node,
											char **line)
{
	uint8_t				errors;
	t_gram_definition	*def;

	*line = ft_strscan(*line);
	errors = 0;
	if (**line == '|' || **line == '=')
	{
		def = gramgen_definition_create();
		if (def)
		{
			(*line)++;
			*line = ft_strscan(*line);
			while (**line)
			{
				if (!add_to_jtable(ir, node, *line))
					logger(CRIT, 2, "grammar_generator", "add to jump table failed!");
				if (**line == '\'')
					errors += gg_process_literal(def, line);
				else if (**line == '<' || **line == '{')
					errors += gg_process_nonterminal(node, def, ir, line);
				else if (ft_isalnum(**line) || **line == '_')
					errors += gg_process_word(def, line);
				*line = ft_strscan(*line);
			}
			if (!vector(&node->definitions, V_PUSHBACK, 0, def))
				gramgen_definition_destroy(def);
		}
	}
	else
		logger(WARN, 3, "grammar_generator",
						"Line doesn't start with '|' or '='",
						*line);
	return (errors);
}
