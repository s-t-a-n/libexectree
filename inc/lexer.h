/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/20 17:03:10 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/23 18:00:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "exectree_internal.h"

t_node *lexer(t_exectree *tree, const char *str);

#endif
