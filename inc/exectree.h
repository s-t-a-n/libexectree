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

typedef enum		e_et_symtype
{
	E_SYM,
	E_SYM_ENCAPS
}					t_et_symtype;

typedef struct		s_et_instruction
{
	const char		*sym;
	t_et_symtype	st;
	void			*(*solver)(	void *subject,
								void *children,
								void *neighbours);
}					t_et_instruction;

void				*exectree_create();
void				*exectree_destroy(void *_tree);

void				*exectree_populate(void *_tree, t_et_instruction in);
void				*exectree_parse(void *_tree, const char *str);
void				*exectree_execute(void *_tree);

#endif
