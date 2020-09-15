
#ifndef LEXER_IR_H
# define LEXER_IR_H

typedef enum				s_lex_definition_type
{
	NONTERMINAL,
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
	t_lex_definition_type	type;
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
	unsigned int			size;
}							t_lexer_ir;

t_lexer_ir					*lexer_generator(const char *bnf_fpath);
t_lexer_ir					*lexer_generator_destroy(t_lexer_ir *ir);
#endif
