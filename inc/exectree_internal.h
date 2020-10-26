/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_internal.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:38:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:31:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_INTERNAL_H
# define EXECTREE_INTERNAL_H

# ifdef DEBUG
#  include <stdio.h>
# endif

# include "exectree.h"
# include "grammar_ir.h"
# include "tree.h"

typedef struct		s_exectree
{
	t_grammar_ir	*gram_ir;
	t_node			*lex_tree;
	t_node			*parse_tree;
}					t_exectree;

#endif
