/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_ir_lifetime.c                                :+:    :+:            */
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

#include "lexergenerator.h"

t_lexer_ir		*lexer_ir_create(void)
{
	t_lexer_ir	*ir;

	ir = ft_calloc(sizeof(t_lexer_ir), 1);
	if (ir)
	{
		if (!vector(&ir->nodes, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(ir);
			return (NULL);
		}
	}
	return (ir);
}

t_lexer_ir		*lexer_ir_destroy(t_lexer_ir *ir)
{
	unsigned int i;

	if (ir)
	{
		while (*(size_t *)vector(&ir->nodes, V_SIZE, 0, NULL) > 0)
		{
			lexgen_node_destroy(vector(&ir->nodes, V_PEEKBACK, 0, NULL));
			vector(&ir->nodes, V_POPBACK, 0, NULL);
		}
		i = 0;
		while (i < JTAB_SIZE)
			lst_destroy(&ir->jtable[i++], false);
		vector(&ir->nodes, V_DESTROY, false, NULL);
	}
	free(ir);
	return (NULL);
}
