/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 21:44:44 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

void	*exectree_create(const char *bnf_fpath);
void	*exectree_destroy(void *tree);

void	*exectree_parse(void *tree, char *str);

void	*exectree_execute(void *tree);

#endif
