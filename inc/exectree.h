/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/20 19:06:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

# ifdef DEBUG
#  include <stdio.h>
# endif

void				*exectree_create();
void				*exectree_destroy(void *_tree);

void				*exectree_populate(void *_tree, t_token *_token);
void				*exectree_build(void *_tree, const char *str);
void				*exectree_execute(void *_tree);

#endif
