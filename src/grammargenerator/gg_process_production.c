/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_production.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:09 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:52:22 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "grammargenerator.h"

t_gram_production				*gramgen_process_new_production(t_grammar_ir *ir, char **line)
{
	t_gram_production			*production;
	char				*key;
	size_t				keylen;
	t_gram_production_type	type;

	keylen = ft_strcsetlen(*line, PRODUCTION_CLOSESET);
	if ((key = ft_strsub(*line, 0, keylen)))
	{
		type = ft_islower(*key) ? PARSER_OBJECT : LEXER_OBJECT;
		if ((production = gramgen_production_create(ft_strtolower(key), type)))
		{
			if (vector(&ir->productions, V_PUSHBACK, 0, production))
			{
				logger(INFO, 3, "grammar_generator",
								"Pushing non-terminal",
								production->nonterminal);
				*line += ft_strclen(*line, '=');
				ir->size++;
				return (production);
			}
			return (gramgen_production_destroy(production));
		}
		free(key);
	}
	return (NULL);
}
