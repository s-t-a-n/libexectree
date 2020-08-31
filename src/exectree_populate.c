#include "exectree_internal.h"

void	*exectree_populate(void *_tree,
			const char *sym,
			t_et_nodetype nt,
			void *(*solver)(void *subject, void *children, void *neighbours))
{
	(void)sym;
	(void)nt;
	(void)solver;
	return (_tree);
}
