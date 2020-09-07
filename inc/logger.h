/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 22:35:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 15:14:25 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

#include <stdarg.h>

# define LOG_BUF_SIZE 1024

# define STD_OUT			1
# define STD_ERR			2

typedef enum		e_error
{
	INFO,
	WARN,
	CRIT
}					t_error;

void				logger(	t_error errl,
							unsigned int argc,
							...);
#endif
