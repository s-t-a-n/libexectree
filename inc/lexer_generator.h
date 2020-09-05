/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:08:27 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 22:02:41 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_GENERATOR_H
# define LEXER_GENERATOR_H

#ifdef DEBUG
# include <stdio.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "vector.h"

typedef struct		s_lex_object
{
	char			*nonterminal;
	void			*options;
}					t_lex_object;

typedef struct		s_lexer_ir
{
	void			*vec_lex_objects;
	void			*non_terminals;
	unsigned int	size;
}					t_lexer_ir;

t_lexer_ir			*lexer_generator(const char *bnf_fpath);

/*
** internal functions
*/
t_lexer_ir	*lexer_generator_create();
t_lexer_ir	*lexer_generator_destroy(t_lexer_ir *ir);

t_lexer_ir	*lexer_generator_create_ir(t_lexer_ir *ir, int fd);

#endif
