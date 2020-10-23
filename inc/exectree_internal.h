/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_internal.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:38:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/23 19:13:23 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_INTERNAL_H
# define EXECTREE_INTERNAL_H

# ifdef DEBUG
#  include <stdio.h>
# endif

# include "exectree.h"
# include "lexer_ir.h"
# include "node.h"

typedef struct	s_exectree
{
	t_lexer_ir	*lex_ir;
	t_node		*lex_tree;
	t_node		*parse_tree;
}				t_exectree;

#endif
