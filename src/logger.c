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
#include "logger.h"

/*
** Excuse the overhead when DEBUG is unset; 42 doesn't allow macro's..
** Current LOG_BUF_SIZE overflow is not handled; capping all output messages
** to LOG_BUG_SIZE. Also, use of strlcat is not very optimized. 
*/

#ifdef DEBUG

const static char	*colors[3] = {
	[INFO] = "\x1b[32;01m",
	[WARN] = "\x1b[33;01m",
	[CRIT] = "\x1b[31;01m"
};

void	logger(	t_error errl,
				unsigned int argc,
				...)
{
	va_list	args;
	unsigned int i;
	char	buffer[LOG_BUF_SIZE];
	
	va_start(args, argc);
	buffer[0] = '\0';
	ft_strlcat(buffer, colors[errl], LOG_BUF_SIZE);
	ft_strlcat(buffer, va_arg(args, char *), LOG_BUF_SIZE);
	ft_strlcat(buffer, "\x1b[0m -> ", LOG_BUF_SIZE);
	i = 1;
	while(i < argc)
	{
			ft_strlcat(buffer, va_arg(args, char *), LOG_BUF_SIZE);
			if (i < argc - 1)
				ft_strlcat(buffer, " : ", LOG_BUF_SIZE);
			i++;
	}
	ft_strlcat(buffer, "\n", LOG_BUF_SIZE);
	write(errl == INFO ? STD_OUT : STD_ERR, buffer, ft_strlen(buffer));
}

#else

void	logger(	t_error errl,
				unsigned int argc,
				...)
{
	return ;
	(void)errl;
	(void)argc;
}

#endif
