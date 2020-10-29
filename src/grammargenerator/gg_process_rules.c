/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_rules.c                              :+:    :+:            */
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

uint8_t					gramgen_process_rules(t_grammar_ir *ir,
											t_gram_production *production,
											char **line)
{
	uint8_t				errors;
	t_gram_rule	*def;

	*line = ft_strscan(*line);
	errors = 0;
	if (**line == '|' || **line == '=')
	{
		def = gramgen_rule_create();
		if (def)
		{
			(*line)++;
			*line = ft_strscan(*line);
			while (**line)
			{
//				if (!add_to_jtable(ir, production, *line))
//					logger(CRIT, 2, "grammar_generator", "add to jump table failed!");
				if (ft_isinset(**line, "'"))
					errors += gg_process_literal(def, line);
				else if (ft_isinset(**line, PRODUCTION_OPENSET))
					errors += gg_process_nonterminal(production, def, ir, line);
				else if (ft_isalnum(**line) || **line == '_')
					errors += gg_process_word(def, line);
				*line = ft_strscan(*line);
			}
			if (!vector(&production->rules, V_PUSHBACK, 0, def))
				gramgen_rule_destroy(def);
		}
	}
	else
		logger(WARN, 3, "grammar_generator",
						"Line doesn't start with '|' or '='",
						*line);
	return (errors);
}
