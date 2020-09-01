/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exectree.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 19:37:59 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/01 19:47:18 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECTREE_H
# define EXECTREE_H

typedef struct		s_token t_token;

typedef enum		e_symtype
{
	E_SYM,
	E_SYM_ENCAPS
}					t_symtype;

typedef enum		e_nodetype
{
	E_EXPRESSION,
	E_STATEMENT
}					t_nodetype;

typedef struct		s_token
{
	unsigned char	*symbol;
	t_symtype		symtype;
	t_nodetype		nodetype;
	void			*(*solver)(	void *subject,
								void *children,
								void *neighbours);
	t_token			*next;
}					t_token;

void				*exectree_create();
void				*exectree_destroy(void *_tree);

void				*exectree_populate(void *_tree, t_token *_token);
void				*exectree_parse(void *_tree, const char *str);
void				*exectree_execute(void *_tree);

#endif
