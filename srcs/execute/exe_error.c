/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:46:40 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/17 19:46:12 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	exit_err_pro(t_command **cmd)
{
	cmd_list_free(cmd);
	exit(1);
}

void	cmd_not_found(char *file, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		exit(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void	specific_path_error(char *path)
{
	if (ft_strcmp(path, ".") == 0)
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(1);
	}
	else if (ft_strcmp(path, "..") == 0)
	{
		ft_putendl_fd("minishell: ..: command not found", 2);
		exit(1);
	}
	else if (ft_strcmp(path, "/") == 0)
	{
		ft_putendl_fd("minishell: /: is a directory", 2);
		exit(1);
	}
	else
	{
		ft_putendl_fd("minishell: : command not found", 2);
		exit(1);
	}
}
