#include "grammargenerator.h"
#include "exectree_internal.h"

void			*exectree_create(const char *bnf_fpath)
{
	t_exectree	*exectree;

	exectree = ft_calloc(sizeof(t_exectree), 1);
	if (exectree)
	{
		if (!(exectree->gram_ir = grammar_ir_generate(bnf_fpath)))
			return(exectree_destroy(exectree));
	}
	return (exectree);
}

void			*exectree_destroy(void *_exectree)
{
	t_exectree *exectree;

	if (_exectree)
	{
		exectree = (t_exectree *)_exectree;
		exectree->gram_ir = grammar_ir_destroy(exectree->gram_ir);
	}
	free(_exectree);
	return (NULL);
}
