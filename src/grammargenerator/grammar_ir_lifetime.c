/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grammar_ir_lifetime.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:48 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:11:13 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vector.h"

#include "grammargenerator.h"

t_grammar_ir		*grammar_ir_create(void)
{
	t_grammar_ir	*ir;

	ir = ft_calloc(sizeof(t_grammar_ir), 1);
	if (ir)
	{
		if (!vector(&ir->productions, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(ir);
			return (NULL);
		}
	}
	return (ir);
}

t_grammar_ir		*grammar_ir_destroy(t_grammar_ir *ir)
{
	unsigned int i;

	if (ir)
	{
		while (*(size_t *)vector(&ir->productions, V_SIZE, 0, NULL) > 0)
		{
			gramgen_production_destroy(vector(&ir->productions, V_PEEKBACK, 0, NULL));
			vector(&ir->productions, V_POPBACK, 0, NULL);
		}
		i = 0;
		while (i < SYMBOL_SETSIZE)
			lst_destroy(&ir->lex_jtable[i++], FALSE);
		vector(&ir->productions, V_DESTROY, FALSE, NULL);
	}
	free(ir);
	return (NULL);
}
