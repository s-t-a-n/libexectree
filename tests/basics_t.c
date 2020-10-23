/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basics_t.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 19:36:36 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 22:46:08 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "exectree.h"

int				main(int argc, char **argv)
{
	if (argc == 3)
	{
		void *tree = exectree_create(argv[1]);
		assert(tree);
		assert(exectree_parse(tree, argv[2]));
		assert(exectree_destroy(tree) == NULL);
		return (0);
	}
	else
		return (1);
}
