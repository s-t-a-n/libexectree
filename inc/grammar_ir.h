
#ifndef GRAMMAR_IR_H
# define GRAMMAR_IR_H

# include "libft.h"

# define JTAB_SIZE	127

/*
** To protect sanity:
** An intermediate representation of the formal syntax grammer (as supplied
** by an BNF file) consists of a vector of nodes which each define one
** non-terminal. These non-terminal are then each defined as a vector of
** definitions. Each definition is then defined as a vector of 'tokens'
** which could be a non-terminal or terminal
*/

typedef enum				s_gram_definition_type
{
	NONTERMINAL,
	NONTERMINAL_MULT,
	UNBOUND_NONTERMINAL,
	UNBOUND_NONTERMINAL_MULT,
	TERMINAL,
	UNKNOWN
}							t_gram_definition_type;

/*
** sig can be a reference to a definition or be a charstring
** signifying a terminal
*/
typedef struct				s_gram_token
{
	t_gram_definition_type	type;
	void					*sig;
}							t_gram_token;

typedef struct				s_gram_definition
{
	void					*tokens;
}							t_gram_definition;

typedef enum				s_gram_node_type
{
	PARSER_OBJECT,
	LEXER_OBJECT
}							t_gram_node_type;

typedef struct				s_gram_node
{
	t_gram_node_type		type;
	char					*nonterminal;
	void					*definitions;
}							t_gram_node;

/*
** jtable contains nodes where first letter of terminal matches as index
*/
typedef struct				s_grammar_ir
{
	void					*nodes;
	t_list					*post;
	t_list					*jtable[JTAB_SIZE];
	unsigned int			size;
}							t_grammar_ir;


t_grammar_ir				*grammar_ir_generate(const char *bnf_fpath);

void						grammar_ir_dump(t_grammar_ir *ir);
t_grammar_ir				*grammar_ir_destroy(t_grammar_ir *ir);

t_gram_node					*grammar_ir_find_node(t_grammar_ir *ir, char *key);

#endif
