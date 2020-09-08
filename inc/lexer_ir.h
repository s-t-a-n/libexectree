
#ifndef LEXER_IR_H
# define LEXER_IR_H

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
t_lexer_ir			*lexer_generator_destroy(t_lexer_ir *ir);
#endif
