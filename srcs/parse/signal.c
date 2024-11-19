/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 08:55:42 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/17 08:55:59 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	handler_int(int signal)
{
	pid_t	pid;
	int		stat;

	pid = waitpid(-1, &stat, WNOHANG);
	if (signal == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			close(STDIN_FILENO);
		}
	}	
}

void	set_sig(void)
{
	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
}

void	get_sig(void)
{
	signal(SIGQUIT, SIG_DFL);
}
