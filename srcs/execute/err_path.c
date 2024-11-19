/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 03:54:50 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/09 23:56:24 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	is_dir(char *path)
{
	struct stat	d_stat;

	if (stat(path, &d_stat) == 0)
	{
		if ((d_stat.st_mode) == 0)
		{
			ft_putstr_fd("minihsell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": is a directory", 2);
			exit(126);
		}
	}
}

char	*absolute_path_set(char *path)
{
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0 \
			|| path[0] == '\0' || ft_strcmp(path, "/") == 0)
		specific_path_error(path);
	if (access(path, F_OK) == 0)
		return (path);
	cmd_not_found(path, 0);
	return (NULL);
}

char	*path_parse(char **cmd, t_data *data)
{
	char	*absolute_path;
	char	**split;
	char	*slash;
	int		i;

	if (cmd[0][0] == '/' || cmd[0][0] == '.' || cmd[0][0] == '\0')
		return (absolute_path_set(cmd[0]));
	split = ft_split(ft_getenv("PATH", data->env), ':');
	i = -1;
	while (split[++i])
	{
		slash = ft_strjoin(split[i], "/");
		absolute_path = ft_strjoin(slash, cmd[0]);
		if (access(absolute_path, F_OK) == 0)
		{
			free(slash);
			free_arr(split);
			return (absolute_path);
		}
		free(slash);
		free(absolute_path);
	}
	cmd_not_found(cmd[0], 1);
	return (NULL);
}
