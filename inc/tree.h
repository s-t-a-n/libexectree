/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 20:31:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:31:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct	s_node t_node;
typedef struct	s_node
{
	t_node		*parent;
	t_node		*left;
	t_node		*right;
	void		*children;
}				t_node;

t_node			*node_create();
t_node			*node_destroy(t_node *node);

#endif
