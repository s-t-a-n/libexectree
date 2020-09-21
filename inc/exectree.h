/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/20 19:50:08 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

void	*exectree_create(const char *bnf_fpath);
void	*exectree_destroy(void *tree);

void	*exectree_single_parse(void *_exectree, const char *str);
void	*exectree_multi_parse(void *_exectree, const char *str); // feed NULL, then lines, then NULL again

void	*exectree_execute(void *tree);

#endif
