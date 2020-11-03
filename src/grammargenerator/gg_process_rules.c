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
	t_gram_rule	*rule;

	errors = 0;
	if (ft_isinset(**line, "|="))
	{
		rule = gramgen_rule_create();
		if (rule)
		{
			(*line)++;
			while (**line)
			{
				*line = ft_strscan(*line);
				if (ft_isinset(**line, "'\"") || ft_isalnum(**line) || **line == '_')
					errors += gg_process_terminal(ir, rule, production, line);
				else if (ft_isinset(**line, PRODUCTION_OPENSET))
					errors += gg_process_nonterminal(ir, rule, line);
			}
			if (!vector(&production->rules, V_PUSHBACK, 0, rule))
				gramgen_rule_destroy(rule);
		}
	}
	else
		logger(WARN, 3, "grammar_generator",
						"Line doesn't start with '|' or '='",
						*line);
	return (errors);
}
