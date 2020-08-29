/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/08/28 19:38:09 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

typedef enum	e_et_nodetype
{
	E_SYM,
	E_SYM_ENCAPS
}				t_et_nodetype;

void	*exectree_create();
void	*exectree_destroy();

#endif
