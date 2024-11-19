/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:00:59 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/18 00:54:58 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	pipe_set(pid_t pid, t_command *cur, int fd[])
{
	if (pid == 0)
	{
		dup2(cur->infile, STDIN_FILENO);
		if (cur->outfile == 1)
			dup2(fd[1], STDOUT_FILENO);
		else
		{
			dup2(cur->outfile, STDOUT_FILENO);
			close(fd[WRITE]);
		}
		close(fd[READ]);
	}
	else
	{
		if (cur->infile != 0)
			close(cur->infile);
		close(fd[WRITE]);
		if (cur->next->infile == 0)
			cur->next->infile = fd[READ];
	}
}

void	last_pipe_set(pid_t pid, t_command *cur, int fd[])
{
	if (pid == 0)
	{
		dup2(cur->infile, STDIN_FILENO);
		dup2(cur->outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	only_built_set(pid_t pid, t_command *cur, int fd[])
{
	if (pid > 0)
	{
		dup2(cur->infile, STDIN_FILENO);
		dup2(cur->outfile, STDOUT_FILENO);
		close(fd[READ]);
		close(fd[WRITE]);
		if (cur->outfile != STDOUT_FILENO)
			close(cur->outfile);
		close(cur->infile);
	}
	else
	{
		close(fd[READ]);
		close(fd[WRITE]);
	}
}

void	set_fd(pid_t pid, t_command *cur, int fd[])
{
	if (cur->next != NULL)
		pipe_set(pid, cur, fd);
	else if (cur->next == NULL && is_built(cur) && cur->cmd_index == 0)
		only_built_set(pid, cur, fd);
	else if (cur->next == NULL)
		last_pipe_set(pid, cur, fd);
}

void	set_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		g_exit_status = 130;
	}
	else if (status == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3\n", STDERR_FILENO);
		g_exit_status = 131;
	}
	else
		g_exit_status = WEXITSTATUS(status);
}
