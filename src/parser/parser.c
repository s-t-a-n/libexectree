/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 21:16:44 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 22:48:50 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

//static t_node	*match(	t_lexer_ir *ir,
//						t_node **tree,
//						char  *str)
//{
//	
//}
//
//t_node			*parser(t_lexer_ir *ir, char *str)
//{
//	t_node	*tree;
//	// iterate over string from left to right
//	// find widest possible terminal definition for every object using right derivation, bottum up
//	// expand definition to more abstract forms
//	// check if multiple solutions exists using backtracking with stack
//
//	tree = NULL;
//	while(*str)
//	{
//		str = ft_strscan(str);
//		if (!match(ir, &tree, str))
//			return(tree_destroy(tree));
//		// increment is done in functions
//	}
//
//	(void)ir; // STUB
//	(void)str; // STUB
//	return (NULL); // STUB
//}
