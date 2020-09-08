/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 18:08:27 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 18:33:24 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_GENERATOR_H
# define LEXER_GENERATOR_H

#ifdef DEBUG
# include <stdio.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define VEC_DEF_SIZE	24

typedef enum		s_lex_definition_type
{
	NONTERMINAL,
	TERMINAL
}					t_lex_definition_type;

typedef struct		s_lex_definition
{
	t_lex_definition_type type;
	char			*terminal;
	void			*nonterminal;
}					t_lex_definition;

typedef struct		s_lex_object
{
	char			*nonterminal;
	void			*definitions;
}					t_lex_object;

typedef struct		s_lexer_ir
{
	void			*vec_lex_objects;
	unsigned int	size;
}					t_lexer_ir;

t_lexer_ir			*lexer_generator(const char *bnf_fpath);

/*
** internal functions
*/

t_lexer_ir			*lexer_generator_create_ir(t_lexer_ir *ir, int fd);

t_lexer_ir			*lexer_generator_create();
t_lexer_ir			*lexer_generator_destroy(t_lexer_ir *ir);

t_lex_object		*process_new_nonterminal(t_lexer_ir *ir, char **line);
uint8_t				process_definitions(t_lexer_ir *ir, t_lex_object *obj, char **line);

t_lex_object		*lexer_object_create(char *nonterminal);
t_lex_object		*lexer_object_destroy(t_lex_object *obj);

t_lex_definition	*lexer_definition_create(	t_lex_definition_type type,
												char *terminal,
												t_lex_object *nonterminal);
t_lex_definition	*lexer_definition_destroy(t_lex_definition *def);

#endif
