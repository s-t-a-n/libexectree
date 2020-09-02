/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basics_t.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 19:36:36 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 22:46:08 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exectree.h"

void			*endofstatement_solver(void *subject,
									void *children,
									void *neighbours)
{
	(void)subject;
	(void)children;
	return (neighbours);
}

void			*echo_solver(void *subject,
									void *children,
									void *neighbours)
{
	(void)subject;
	(void)children;
	return (neighbours);
}

void			*variable_solver(void *subject,
									void *children,
									void *neighbours)
{
	(void)subject;
	(void)children;
	return (neighbours);
}

static t_token	tokens[TOKENTABLE_SIZE] = 
{
	[1] = {";", 1, E_SYM, E_STATEMENT, endofstatement_solver, E_STATIC, NULL},
	[2] = {"echo ", 5, E_SYM, E_STATEMENT, echo_solver, E_STATIC, NULL},
	[3] = {"$", 1, E_SYM, E_EXPRESSION, variable_solver, E_STATIC, NULL},
};

int				main(void)
{
	void *tree = exectree_create();
	exectree_populate(tree, &tokens[1]);
	exectree_populate(tree, &tokens[2]);
	exectree_build(tree, "echo a ; echo b");

	exectree_destroy(tree);
	system("leaks basics_t.testbin");
	return (0);
}
