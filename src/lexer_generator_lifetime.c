/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_lifetime.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:28:05 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 21:52:00 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "lexer_generator.h"

t_lexer_ir		*lexer_generator_create()
{
	t_lexer_ir	*ir;

	ir = ft_calloc(sizeof(t_lexer_ir), 1);
	if (ir)
	{
		vector(&ir->vec_lex_objects, V_CREATE, 24, NULL);
		vector(&ir->non_terminals, V_CREATE, 24, NULL);
	}
	return (ir);
}

t_lexer_ir		*lexer_generator_destroy(t_lexer_ir *ir)
{
	free(ir);
	return(NULL);
}
