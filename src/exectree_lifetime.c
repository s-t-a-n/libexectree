
#include "exectree_internal.h"

void		*exectree_create()
{
	return((void *)tree_create());
}

void		*exectree_destroy(void *_tree)
{
	return((void *)tree_destroy((t_tree *)_tree));
}

/*
void		*exectree_populate(void *_tree)
{

}

void		*exectree_parse(void *_tree, const char *str)
{

}

void		*exectree_execute(void *_tree)
{

}
*/
