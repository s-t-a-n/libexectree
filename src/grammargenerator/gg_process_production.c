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

static t_gram_production		*new_production(t_grammar_ir *ir,
												char **line,
												char *key)
{
	t_gram_production			*production;
	t_gram_production_type		type;

	type = ft_islower(*key) ? PARSER_OBJECT : LEXER_OBJECT;
	if ((production = gramgen_production_create(ft_strtolower(key), type)))
	{
		if (vector(&ir->productions, V_PUSHBACK, 0, production))
		{
			logger(INFO, 3, "grammar_generator",
							"Pushing new non-terminal",
							production->nonterminal);
			*line += ft_strclen(*line, '=');
			ir->size++;
			return (production);
		}
		return (gramgen_production_destroy(production));
	}
	free(key);
	return (NULL);
}

static t_gram_production		*new_production_subkey(	t_grammar_ir *ir,
														char **line,
														char *key,
														char *subkey)
{
	// not implemented yet
	return (new_production(ir, line, key));
	(void)subkey;
}

t_gram_production				*gramgen_process_new_production(t_grammar_ir *ir, char **line)
{
	char						*head;
	char						*key;
	char						*subkey;

	if ((head = ft_strnstr(*line, "->", ft_strclen(*line, ':'))))
	{
		if ((subkey = ft_strsub(head, 2, ft_strcsetlen(head + 2, PRODUCTION_CLOSESET))))
		{
			if (!(key = ft_strsub(*line, 0, (size_t)head - (size_t)*line)))
			{
				free(subkey);
				return (NULL);
			}
			return (new_production_subkey(ir, line, key, subkey));
		}
	}
	else
	{
		if ((key = ft_strsub(*line, 0, ft_strcsetlen(*line, PRODUCTION_CLOSESET))))
			return (new_production(ir, line, key));
	}
	return (NULL);
}
