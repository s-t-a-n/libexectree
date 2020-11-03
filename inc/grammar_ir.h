
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
	NONTERMINAL				= 1<<0,
	NONTERMINAL_MULT		= 1<<1,
	UNBOUND_NONTERMINAL		= 1<<2,
	UNBOUND_NONTERMINAL_MULT= 1<<3,
	RECURSIVE_NONTERMINAL	= 1<<4,
	TERMINAL				= 1<<5,
	UNKNOWN					= 1<<6
}							t_gram_rule_type;

# define MULTI_RULETYPES	(NONTERMINAL_MULT|UNBOUND_NONTERMINAL_MULT)

typedef struct				s_gram_production t_gram_production;
typedef struct				s_gram_token
{
	t_gram_rule_type		type;
	void					*production; // vector in case of multi rule type
	char					*terminal;
}							t_gram_token;

typedef struct				s_gram_rule
{
	t_vector				*tokens;
}							t_gram_rule;

typedef enum				s_gram_production_type
{
	PARSER_OBJECT,
	LEXER_OBJECT
}							t_gram_production_type;

typedef struct				s_gram_production
{
	t_gram_production_type	type;
	char					*nonterminal;
	t_vector				*rules;
	t_vector				*references; // references from other productions
}							t_gram_production;

typedef struct				s_grammar_ir
{
	t_vector				*productions;
	t_list					*post;
	t_list					*lex_jtable[SYMBOL_SETSIZE]; // add for every terminal an entry based on the first letter
	unsigned int			size;
}							t_grammar_ir;

t_grammar_ir				*grammar_ir_generate(const char *bnf_fpath);

void						grammar_ir_dump(t_grammar_ir *ir);
t_grammar_ir				*grammar_ir_destroy(t_grammar_ir *ir);

t_gram_production			*grammar_ir_find_production(t_grammar_ir *ir,
														char *key);

#endif
