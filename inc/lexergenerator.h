
#ifndef LEXERGENERATOR_H
# define LEXERGENERATOR_H

#ifdef DEBUG
# include <stdio.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "lexer_ir.h"

# define VEC_DEF_SIZE	24

t_lexer_ir			*lexer_generator_create_ir(t_lexer_ir *ir, int fd);

t_lexer_ir			*lexer_generator_create();

t_lex_node			*process_new_nonterminal(t_lexer_ir *ir, char **line);
uint8_t				process_definitions(t_lexer_ir *ir, t_lex_node *node, char **line);

t_lex_node			*lexer_node_create(char *nonterminal);
t_lex_node			*lexer_node_destroy(t_lex_node *node);

t_lex_definition	*lexer_definition_create(void);
t_lex_definition	*lexer_definition_destroy(t_lex_definition *def);

t_lex_token			*lexer_token_create(t_lex_definition_type type, void *sig);
t_lex_token			*lexer_token_destroy(t_lex_token *token);

uint8_t				lexer_post_process(t_lexer_ir *ir);

#endif
