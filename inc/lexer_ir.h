
#ifndef LEXER_IR_H
# define LEXER_IR_H

#include "libft.h"

/*
** To protect sanity:
** An intermediate representation of the formal syntax grammer (as supplied
** by an BNF file) consists of a vector of nodes which each define one
** non-terminal. These non-terminal are then each defined as a vector of
** definitions. Each definition is then defined as a vector of 'tokens'
** which could be a non-terminal or terminal
*/

typedef enum				s_lex_definition_type
{
	NONTERMINAL,
	UNKNOWN_NONTERMINAL,
	TERMINAL
}							t_lex_definition_type;

/*
** sig can be a reference to a definition or be a charstring
** signifying a terminal
*/
typedef struct				s_lex_token
{
	t_lex_definition_type	type;
	void					*sig;
}							t_lex_token;

typedef struct				s_lex_definition
{
	void					*tokens;
}							t_lex_definition;

typedef struct				s_lex_node
{
	char					*nonterminal;
	void					*definitions;
}							t_lex_node;

typedef struct				s_lexer_ir
{
	void					*nodes;
	t_list					*post;
	unsigned int			size;
}							t_lexer_ir;


t_lexer_ir					*lexer_generator(const char *bnf_fpath);
void						lexer_generator_dump(t_lexer_ir *ir);
t_lexer_ir					*lexer_generator_destroy(t_lexer_ir *ir);

t_lex_node					*lexer_find_node(t_lexer_ir *ir, char *key);

#endif
