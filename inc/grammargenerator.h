
#ifndef GRAMMARGENERATOR_H
# define GRAMMARGENERATOR_H

#ifdef DEBUG
# include <stdio.h>
# include <assert.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "grammar_ir.h"

# define PRODUCTION_OPENSET		"<{|"
# define PRODUCTION_CLOSESET	">}|"

# define VEC_DEF_SIZE	24

/*
** Internal functions for generating an internal representation of the formal
** syntax grammar. Some functions are ommited since they are presented
** in the grammar_ir.h header.
*/

t_grammar_ir		*grammar_ir_create(void);

t_gram_production			*gramgen_process_new_production(t_grammar_ir *ir, char **line);
uint8_t				gramgen_process_rules(t_grammar_ir *ir, t_gram_production *production, char **line);
uint8_t				gg_process_word(t_gram_rule *def, char **line);
uint8_t				gg_process_literal(t_gram_rule *def, char **line);
uint8_t				gg_process_nonterminal(			t_gram_production *production,
													t_gram_rule *def,
													t_grammar_ir *ir,
													char **line);
uint8_t				gg_process_unbound_nonterminal(	t_gram_production *production,
													t_gram_rule *def,
													t_grammar_ir *ir,
													char **line);

t_gram_production			*gramgen_production_create(char *nonterminal, t_gram_production_type type);
t_gram_production			*gramgen_production_destroy(t_gram_production *production);

t_gram_rule	*gramgen_rule_create(void);
t_gram_rule	*gramgen_rule_destroy(t_gram_rule *def);

t_gram_token		*gramgen_token_create(t_gram_rule_type type, void *sig);
t_gram_token		*gramgen_token_destroy(t_gram_token *token);

void				*gramgen_lex_lookup_add(t_list **tab, char *line, void *subject);

uint8_t				gramgen_post_process(t_grammar_ir *ir);

#endif
