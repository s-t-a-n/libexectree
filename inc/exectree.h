/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/02 22:45:47 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

# ifdef DEBUG
#  include <stdio.h>
# endif

# define TOKENTABLE_SIZE	127

typedef void		*t_vector;

typedef struct		s_token t_token;
typedef struct		s_node t_node;

typedef enum		e_symtype
{
	E_SYM,
	E_SYM_ENCAPS
}					t_symtype;

typedef enum		e_nodetype
{
	E_EXPRESSION,
	E_STATEMENT,
	E_LINKER
}					t_nodetype;

typedef enum		e_malloced
{
	E_MALLOC,
	E_STATIC
}					t_malloced;

typedef struct		s_token
{
	char			*symbol;
	unsigned int	symlen;
	t_symtype		symtype;
	t_nodetype		nodetype;
	void			*(*solver)(	void *subject,
								void *children,
								void *neighbours);
	t_malloced		malloced;
	t_token			*next;
}					t_token;

typedef struct		s_node
{
	t_node			*parent;
	t_vector		neighbour;
	t_vector		children;
	void			*(*solver)(void *subject, void *children, void *neighbours);
	void			*subject;
}					t_node;

void				*exectree_create();
void				*exectree_destroy(void *_tree);

void				*exectree_populate(void *_tree, t_token *_token);
void				*exectree_build(void *_tree, const char *str);
void				*exectree_execute(void *_tree);

#endif
