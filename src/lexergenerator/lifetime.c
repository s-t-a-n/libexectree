/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_lifetime.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:28:05 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 17:51:20 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vector.h"

#include "lexergenerator.h"

t_lexer_ir		*lexer_generator_create()
{
	t_lexer_ir	*ir;

	ir = ft_calloc(sizeof(t_lexer_ir), 1);
	if (ir)
	{
		if (!vector(&ir->vec_lex_objects, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(ir);
			return (NULL);
		}
	}
	return (ir);
}

t_lexer_ir		*lexer_generator_destroy(t_lexer_ir *ir)
{
	while (*(size_t *)vector(&ir->vec_lex_objects, V_SIZE, 0, NULL) > 0)
	{
		lexer_object_destroy(vector(&ir->vec_lex_objects, V_PEEKBACK, 0, NULL));
		vector(&ir->vec_lex_objects, V_POPBACK, 0, NULL);
	}
	vector(&ir->vec_lex_objects, V_DESTROY, false, NULL);
	free(ir);
	return(NULL);
}
