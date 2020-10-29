/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 20:31:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 21:01:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef void	t_vector;
typedef struct	s_node t_node;
typedef struct	s_node
{
	t_node		*parent;
	t_node		*left;
	t_node		*right;
	t_vector	*children;
}				t_node;

t_node			*node_create();
t_node			*node_destroy(t_node *node);

t_node			*tree_create();
t_node			*tree_destroy(t_node *root);

#endif
