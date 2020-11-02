
#ifndef GRAMMAR_IR_H
# define GRAMMAR_IR_H

# include "libft.h"

# define SYMBOL_SETSIZE		127

/*
** To protect sanity:
** An intermediate representation of the formal syntax grammer (as supplied
** by an BNF file) consists of a vector of productions which each define one
** non-terminal. These non-terminal are then each defined as a vector of
** rules. Each rule is then defined as a vector of 'tokens'
** which could be a non-terminal or terminal
*/

typedef void				t_vector;
typedef enum				s_gram_rule_type
{
	NONTERMINAL = 1,
	NONTERMINAL_MULT = 2,
	UNBOUND_NONTERMINAL = 4,
	UNBOUND_NONTERMINAL_MULT = 8,
	RECURSIVE_NONTERMINAL = 16,
	TERMINAL = 32,
	UNKNOWN = 64
}							t_gram_rule_type;

/*
** sig can be a non-terminal referring to a rule (gram_production)
** or be a terminal referring to a char (char-string)
*/

typedef struct				s_gram_token
{
	t_gram_rule_type		type;
	// jtable
	void					*sig;
}							t_gram_token;

typedef struct				s_gram_rule
{
	t_vector				*tokens; // vec
}							t_gram_rule;

typedef enum				s_gram_production_type
{
	PARSER_OBJECT,
	LEXER_OBJECT
}							t_gram_production_type;

typedef struct				s_gram_production
{
	t_gram_production_type		type;
	char					*nonterminal;
	t_vector					*rules;
}							t_gram_production;

/*
** jtable contains productions where first letter of terminal matches as index
*/
typedef struct				s_grammar_ir
{
	t_vector				*productions;
	t_list					*post;
	t_list					*lex_lookup[SYMBOL_SETSIZE];
	t_vector				*parse_lookup; // vec
	unsigned int			size;
}							t_grammar_ir;


t_grammar_ir				*grammar_ir_generate(const char *bnf_fpath);

void						grammar_ir_dump(t_grammar_ir *ir);
t_grammar_ir				*grammar_ir_destroy(t_grammar_ir *ir);

t_gram_production					*grammar_ir_find_production(t_grammar_ir *ir, char *key);

#endif
