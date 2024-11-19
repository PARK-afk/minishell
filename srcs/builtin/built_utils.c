/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:10:47 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/12 04:54:22 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

bool	is_built(t_command *command)
{
	if (command->cmd == NULL)
		return (false);
	if (ft_strncmp(command->cmd[0], "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(command->cmd[0], "unset", 5) == 0)
		return (true);
	return (false);
}

int	exe_built(t_command *command, t_data *data)
{
	if (ft_strncmp(command->cmd[0], "cd", 2) == 0)
		return (ft_cd(command, &data->env));
	else if (ft_strncmp(command->cmd[0], "echo", 4) == 0)
		return (ft_echo(command->cmd));
	else if (ft_strncmp(command->cmd[0], "env", 3) == 0)
		return (ft_env(data->env));
	else if (ft_strncmp(command->cmd[0], "exit", 4) == 0)
		return (ft_exit(command->cmd));
	else if (ft_strncmp(command->cmd[0], "export", 6) == 0)
		return (ft_export(command->cmd, data));
	else if (ft_strncmp(command->cmd[0], "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strncmp(command->cmd[0], "unset", 5) == 0)
		return (ft_unset(command->cmd, data));
	return (0);
}

int	is_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i + 1);
		i++;
	}
	return (false);
}

bool	check_valid(char *s)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(s[0]) == false && s[0] != '_')
		return (false);
	while (s[i])
	{
		if ((s[i]) == '=')
			return (true);
		if (ft_isalnum(s[i]) == false && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
