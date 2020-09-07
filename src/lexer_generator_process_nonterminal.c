/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_process_nonterminal.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 17:45:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 18:19:11 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "lexer_generator.h"

t_lex_object		*process_new_nonterminal(t_lexer_ir *ir, char **line)
{
	t_lex_object	*obj;
	size_t			keylen;

	obj = ft_calloc(sizeof(t_lex_object), 1);
	if (obj)
	{
		if (vector(&obj->definitions, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			keylen = ft_strclen(*line, '>');
			obj->nonterminal = ft_strsub(*line, 0, keylen);
			*line += ft_strclen(*line, '=');
			if (obj->nonterminal)
			{
				logger(INFO, 3, "lexer_generator", "Pushing non-terminal", obj->nonterminal);
				vector(&ir->vec_lex_objects, V_PUSHBACK, 0, obj);
			}
			else
			{
				free(obj);
				return (NULL);
			}
		}
	}
	return (obj);
}
