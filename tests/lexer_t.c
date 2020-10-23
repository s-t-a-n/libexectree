/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_t.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/20 17:09:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/23 17:46:59 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "exectree.h"
#include "lexer_ir.h"
#include "lexer.h"

int				main(int argc, char **argv)
{
	if (argc == 3)
	{
		void *tree = exectree_create(argv[1]);
		assert(tree);
		assert(exectree_parse(tree, argv[2]));
		assert(exectree_destroy(tree) == NULL);
		return (0);
	}
	else
		return (1);
}
