/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree_internal.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:38:12 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/20 19:07:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_INTERNAL_H
# define EXECTREE_INTERNAL_H

# ifdef DEBUG
#  include <stdio.h>
# endif

# include <stdlib.h>

# include "libft.h"

# include "vector.h"
# include "exectree.h"
# include "lexer_ir.h"

typedef struct	s_exectree
{
	t_lexer_ir	*lex_ir;
}				t_exectree;

#endif
