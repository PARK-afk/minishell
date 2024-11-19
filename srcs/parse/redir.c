/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:56:30 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/17 14:47:33 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	*open_here_doc(t_data *real, char *limit)
{
	int			*here_doc_fd;
	int			i;
	const int	size = here_doc_num(real);

	if (size == 0)
		return (NULL);
	here_doc_fd = (int *)malloc(sizeof(int) * size);
	i = 0;
	while (real)
	{
		if (real->type == HEREDOC)
		{
			here_doc_fd[i] = get_infile_heredoc(real, limit);
			i++;
		}
		real = real->next;
	}
	return (here_doc_fd);
}

int	open_infile(char *filename)
{
	int	sq_flag;
	int	dq_flag;
	int	i;

	i = 0;
	sq_flag = 0;
	dq_flag = 0;
	while (filename[i])
	{
		chec_how_qu(&dq_flag, &sq_flag, filename, &i);
		if (filename[i] == '#' || filename[i] == '>' \
		|| filename[i] == '<' || filename[i] == ')' \
		|| filename[i] == '(' || filename[i] == ';' \
		|| filename[i] == '|')
		{
			free(filename);
			g_exit_status = 258;
			return (0);
		}
		i++;
	}
	if (check_qu(sq_flag, dq_flag, filename) != 0)
		return (0);
	return (open(filename, O_RDONLY));
}

int	open_outfile(char *filename, t_data *real)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '#' || filename[i] == '>' \
		|| filename[i] == '<' || filename[i] == ')' \
		|| filename[i] == '(' || filename[i] == ';' \
		|| filename[i] == '|')
		{
			free(filename);
			g_exit_status = 258;
			return (0);
		}
		i++;
	}
	if (real->type == OUTAPPEN)
		return (open(real->str, O_RDWR | O_CREAT | O_APPEND, 0644));
	else
		return (open(real->str, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void	update_command_status(t_data *real, t_command **cmd, int *fd_status)
{
	if (real->type == PIPE_ && (*cmd))
	{
		fd_status = 0;
		(*cmd) = (*cmd)->next;
	}
	else if ((real->type == OUT || real->type == OUTAPPEN) && !*fd_status)
	{
		(*cmd)->outfile = open_outfile(real->str, real);
	}
}

void	open_any_file(t_data *real, t_command *cmd, int *hd)
{
	int	i;
	int	fd_status;

	i = -1;
	fd_status = 0;
	while (real)
	{
		if (real->type == IN || real->type == HEREDOC)
		{
			if (real->type == IN && !fd_status)
			{
				cmd->infile = open_infile(real->str);
				if (cmd->infile == -1)
					fd_status = 1;
			}
			else
				cmd->infile = hd[++i];
		}
		else
			update_command_status(real, &cmd, &fd_status);
		real = real->next;
	}
}
