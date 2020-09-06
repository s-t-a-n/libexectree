/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 22:34:25 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 15:20:51 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "logging.h"

/*
** Excuse the overhead when DEBUG is unset; 42 doesn't allow macro's..
*/

#ifdef DEBUG

void	logger(	t_error errl,
				const char *header,
				const char *body,
				const char *tail)
{
	char	buffer[1024];
	
	buffer[0] = '\0';
	if (errl == CRIT)
		ft_strlcat(buffer, "\x1b[31;01m", LOG_BUF_SIZE);
	else if (errl == WARN)
		ft_strlcat(buffer, "\x1b[33;01m", LOG_BUF_SIZE);
	else
		ft_strlcat(buffer, "\x1b[32;01m", LOG_BUF_SIZE);
	ft_strlcat(buffer, header, LOG_BUF_SIZE);
	ft_strlcat(buffer, "\x1b[0m", LOG_BUF_SIZE);
	ft_strlcat(buffer, " -> ", LOG_BUF_SIZE);
	ft_strlcat(buffer, body, LOG_BUF_SIZE);
	if (tail)
	{
		ft_strlcat(buffer, " : ", LOG_BUF_SIZE);
		ft_strlcat(buffer, tail, LOG_BUF_SIZE);
	}
	ft_strlcat(buffer, "\n", LOG_BUF_SIZE);
	write(errl == INFO ? STD_OUT : STD_ERR, buffer, ft_strlen(buffer));
}

#else

void	logger(	t_error errl,
				const char *header,
				const char *body,
				const char *tail)
{
	(void)errl;
	(void)header;
	(void)body;
	(void)tail;
}

#endif
