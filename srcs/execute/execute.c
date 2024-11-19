/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:03:38 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/18 00:49:10 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	child_execute(t_command *cur, t_data *data)
{
	char	*path;

	if (cur->next == NULL && cur->cmd_index == 0 && is_built(cur))
		exit(0);
	else if (is_built(cur) == 1)
		exit(exe_built(cur, data));
	if (cur->infile < 0 || cur->outfile < 0)
		exit(1);
	path = path_parse(cur->cmd, data);
	is_dir(path);
	get_sig();
	set_originterm();
	execve(path, cur->cmd, data->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(cur->cmd[0], 2);
	exit(1);
}

void	parent_execute(t_command *cur, t_data *data, t_fds *fds)
{
	close(fds->pi_fd[WRITE]);
	if (cur->infile > 0)
		close(cur->infile);
	if (cur->next != NULL && cur->next->infile == 0)
		cur->next->infile = fds->pi_fd[READ];
	if (!cur->next && cur->cmd_index == 0 && is_built(cur))
	{
		g_exit_status = exe_built(cur, data);
		dup2(fds->std_fd[0], STDIN_FILENO);
		dup2(fds->std_fd[1], STDOUT_FILENO);
	}
}

void	cmd_execute(pid_t pid, t_command *cur, t_data *data, t_fds *fds)
{
	if (pid == 0)
	{
		if (cur->infile >= 0 && cur->outfile >= 1 && cur->cmd == NULL)
			exit(0);
		else if (cur->cmd == NULL)
			exit(1);
		child_execute(cur, data);
	}
	else
	{
		if (cur->infile >= 0 && cur->outfile >= 1 && cur->cmd == NULL)
		{
			g_exit_status = 0;
			return ;
		}
		else if (cur->cmd == NULL)
		{
			g_exit_status = 1;
			return ;
		}
		parent_execute(cur, data, fds);
	}
}

void	execute(t_data *data, t_command *cur)
{
	t_fds		fds;
	pid_t		pid;
	int			status;

	if (data->syntax == 1)
		return ;
	fds.std_fd[0] = dup(STDIN_FILENO);
	fds.std_fd[1] = dup(STDOUT_FILENO);
	while (cur)
	{
		if (pipe(fds.pi_fd) == -1)
			exit_err_pro(&cur);
		pid = fork();
		if (pid == -1)
			exit_err_pro(&cur);
		set_fd(pid, cur, fds.pi_fd);
		cmd_execute(pid, cur, data, &fds);
		cur = cur->next;
	}
	set_exit_status(pid);
	while (waitpid(0, &status, 0) > 0)
		;
}
