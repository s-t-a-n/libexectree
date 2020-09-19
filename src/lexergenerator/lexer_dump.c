
/*
** less restrained use of libraries since this is a mere debugging file
*/
#include <assert.h>
#include <stdio.h>

#include "vector.h"
#include "lexergenerator.h"

/*
void	lexer_token_dump(t_lex_token *token)
{

}

void	lexer_definition_dump(t_lex_definition *def)
{

}

void	lexer_node_dump(t_lex_node *node)
{

}
*/

void	lexer_generator_dump(t_lexer_ir *ir)
{
	size_t				i, j, js, k, ks;
	t_lex_node			*node;
	t_lex_definition	*def;
	t_lex_token			*token;

	i = 0;
	printf("#### %15s|%15s ####\n", "Non terminal", "Definition");
	while (i < ir->size)
	{
		node = vector(&ir->nodes, V_PEEKAT, i, NULL);
		assert(node);
		printf("\n**** %15s ****", node->nonterminal);
		js = *(size_t *)vector(&node->definitions, V_SIZE, 0, NULL);
		j = 0;
		while(j < js)
		{
			printf("%15s", "\n| ");
			def = vector(&node->definitions, V_PEEKAT, j, NULL);
			assert(def);
			ks = *(size_t *)vector(&def->tokens, V_SIZE, 0, NULL);
			k = 0;
			while (k < ks)
			{
				token = vector(&def->tokens, V_PEEKAT, k, NULL);
				assert(token);
				if (token->type == TERMINAL)
				{
					printf("%s ", (char *)token->sig);
				}
				else
				{
					// placeholder (NT's are not post stitched yet)
					printf("%s ", "[NT]");
				}
				k++;
			}
			j++;
		}
		i++;
	}
}
