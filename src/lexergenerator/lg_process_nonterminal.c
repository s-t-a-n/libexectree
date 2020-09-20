/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_nonterminal.c                              :+:    :+:            */
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
#include "lexergenerator.h"

t_lex_node		*lexgen_process_new_nonterminal(t_lexer_ir *ir, char **line)
{
	t_lex_node	*node;
	char		*key;
	size_t		keylen;

	keylen = ft_strclen(*line, '>');
	if ((key = ft_strsub(*line, 0, keylen)))
	{
		if ((node = lexgen_node_create(key)))
		{
			if (vector(&ir->nodes, V_PUSHBACK, 0, node))
			{
				logger(INFO, 3, "lexer_generator",
								"Pushing non-terminal",
								node->nonterminal);
				*line += ft_strclen(*line, '=');
				ir->size++;
				return (node);
			}
			return (lexgen_node_destroy(node));
		}
		free(key);
	}
	return (NULL);
}
