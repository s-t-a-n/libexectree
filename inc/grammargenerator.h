
#ifndef GRAMMARGENERATOR_H
# define GRAMMARGENERATOR_H

#ifdef DEBUG
# include <stdio.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "grammar_ir.h"

# define VEC_DEF_SIZE	24

/*
** Internal functions for generating an internal representation of the formal
** syntax grammar. Some functions are ommited since they are presented
** in the grammar_ir.h header.
*/

t_grammar_ir		*grammar_ir_create(void);

t_gram_node			*gramgen_process_new_nonterminal(t_grammar_ir *ir, char **line);
uint8_t				gramgen_process_definitions(t_grammar_ir *ir, t_gram_node *node, char **line);

t_gram_node			*gramgen_node_create(char *nonterminal);
t_gram_node			*gramgen_node_destroy(t_gram_node *node);

t_gram_definition	*gramgen_definition_create(void);
t_gram_definition	*gramgen_definition_destroy(t_gram_definition *def);

t_gram_token		*gramgen_token_create(t_gram_definition_type type, void *sig);
t_gram_token		*gramgen_token_destroy(t_gram_token *token);

uint8_t				gramgen_post_process(t_grammar_ir *ir);

#endif
