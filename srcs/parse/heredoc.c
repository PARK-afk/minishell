/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:57:03 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/18 00:46:33 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	child_heredoc(int fd, char *limit)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strcmp(line, limit) == 0)
			exit(EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	heredoc(int fd, char *limit)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	set_sig();
	if (pid == 0)
	{
		child_heredoc(fd, limit);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			WEXITSTATUS(status);
	}
	return (status);
}

char	*crate_here_name(void)
{
	int		no_fd;
	char	*itoa_fd;
	char	*here_name;

	no_fd = 0;
	itoa_fd = ft_itoa(no_fd);
	here_name = ft_strjoin("/tmp/here_tmp_", itoa_fd);
	if (access(here_name, F_OK) == 0)
	{
		no_fd++;
		free(itoa_fd);
		free(here_name);
		itoa_fd = ft_itoa(no_fd);
		here_name = ft_strjoin(here_name, itoa_fd);
	}
	free(itoa_fd);
	return (here_name);
}

int	get_infile_heredoc(t_data *data, char *limit)
{
	int		infile;
	int		exit_status;
	char	*file_name;
	char	*dol;

	file_name = crate_here_name();
	infile = open(file_name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (check_dollar(limit))
		dol = substitution_dollar(limit, data->env);
	else
		dol = ft_strdup(limit);
	exit_status = heredoc(infile, dol);
	free(dol);
	close(infile);
	if (exit_status == EXIT_SUCCESS)
		infile = open(file_name, O_RDONLY);
	unlink(file_name);
	free(file_name);
	return (infile);
}
