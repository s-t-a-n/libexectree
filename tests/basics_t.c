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

int				main(void)
{
	void *tree = exectree_create();
	assert(tree);
	assert(exectree_destroy(tree) == NULL);
	return (0);
}
