/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logging.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 22:35:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 22:38:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

typedef enum		e_error
{
	INFO,
	WARN,
	CRIT
}					t_error;

void				logger(	t_error errl,
							const char *header,
							const char *body,
							const char *tail);
#endif
