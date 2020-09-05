/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 22:34:25 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/05 22:38:55 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "logging.h"

void	logger(	t_error errl,
				const char *header,
				const char *body,
				const char *tail)
{
	if (errl == CRIT)
		write(2, "\x1b[31;01m", 10);
	else if (errl == WARN)
		write(2, "\x1b[33;01m", 10);
	else
		write(2, "\x1b[32;01m", 10);
	write(2, header, ft_strlen(header));
	write(2, "\x1b[0m", 6);
	write(2, " -> ", 4);
	write(2, body, ft_strlen(body));
	write(2, " :` ", 3);
	write(2, tail, tail ? ft_strlen(tail) : 0);
}
