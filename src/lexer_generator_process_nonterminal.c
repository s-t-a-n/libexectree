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
	char			*key;
	size_t			keylen;

	keylen = ft_strclen(*line, '>');
	if ((key = ft_strsub(*line, 0, keylen)))
	{
		if ((obj = lexer_object_create(key)))
		{
			if (vector(&ir->vec_lex_objects, V_PUSHBACK, 0, obj))
			{
				logger(INFO, 3, "lexer_generator", "Pushing non-terminal", obj->nonterminal);
				*line += ft_strclen(*line, '=');
				ir->size++;
				return(obj);
			}
			return(lexer_object_destroy(obj));
		}
		free(key);
	}
	return(NULL);
}
