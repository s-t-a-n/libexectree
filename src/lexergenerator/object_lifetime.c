
#include "libft.h"
#include "vector.h"
#include "lexergenerator.h"

t_lex_object	*lexer_object_create(char *nonterminal)
{
	t_lex_object *obj;

	obj = ft_calloc(sizeof(t_lex_object), 1);
	if(obj)
	{
		if(!vector(&obj->definitions, V_CREATE, VEC_DEF_SIZE, NULL))
		{
			free(obj);
			return (NULL);
		}
		obj->nonterminal = nonterminal;
	}
	return (obj);
}

t_lex_object	*lexer_object_destroy(t_lex_object *obj)
{
	while(*(size_t *)vector(&obj->definitions, V_SIZE, 0, NULL) > 0)
	{
		lexer_definition_destroy(vector(&obj->definitions, V_PEEKBACK, 0, NULL));
		vector(&obj->definitions, V_POPBACK, 0, NULL);
	}
	vector(&obj->definitions, V_DESTROY, 0, NULL);
	free(obj->nonterminal);
	free(obj);
	return (NULL);
}
