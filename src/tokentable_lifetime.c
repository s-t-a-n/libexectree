/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokentable_lifetime.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 18:40:13 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 20:14:19 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exectree_internal.h"

t_tokentable		*tokentable_create(size_t _size)
{
	t_tokentable	*tokentable;

	tokentable = ft_calloc(sizeof(t_tokentable), 1);
	if (tokentable)
	{
		tokentable->size = _size;
		tokentable->tokens = ft_calloc(sizeof(void *), _size);
	}
	return (tokentable);
}

t_tokentable		*tokentable_destroy(t_tokentable *tokentable)
{
	t_token			*old;
	t_token			*token;

	while (tokentable->size > 0)
	{
		token = tokentable->tokens[tokentable->size - 1];
		while (token && token->malloced == E_MALLOC)
		{
			old = token;
			token = token->next;
			free(old);
		}
		tokentable->size--;
	}
	free(tokentable);
	return (NULL);
}
