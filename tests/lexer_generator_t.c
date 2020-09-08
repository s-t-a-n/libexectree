/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_t.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 19:16:52 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 19:19:41 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "lexer_generator.h"

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_lexer_ir *ir = lexer_generator(argv[1]);
		if (ir)
			printf("CREATED LEXER IR SUCCESFULLY!\n");
		lexer_generator_destroy(ir);
		return (0);
	}
	else
		return (1);
}
