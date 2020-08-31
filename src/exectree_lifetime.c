
#include "exectree_internal.h"

void		*exectree_create()
{
	return((void *)tree_create());
}

void		*exectree_destroy(void *_tree)
{
	return((void *)tree_destroy((t_tree *)_tree));
}
