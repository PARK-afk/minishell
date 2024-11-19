/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 01:59:07 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/10 01:30:35 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int		export_env_add(char *cmd, char end, t_data *data);
void	update_env_value(char *cmd, char *name, t_data *data);
void	update_env_add(char *cmd, t_data *data);

void	creat_env(char *add, t_data *data)
{
	char	**tmp;
	int		i;
	int		env_size;

	env_size = 0;
	while (data->env[env_size])
		env_size++;
	tmp = ft_calloc(sizeof(char *), env_size + 2);
	if (!tmp)
		exit(1);
	i = -1;
	while (data->env[++i])
		tmp[i] = ft_strdup(data->env[i]);
	tmp[env_size] = ft_strdup(add);
	tmp[env_size + 1] = NULL;
	free_arr(data->env);
	data->env = tmp;
}

void	update_env_value(char *cmd, char *name, t_data *data)
{
	int		i;
	int		flag;
	char	**dup_env;

	flag = 0;
	i = 0;
	dup_env = data->env;
	while (dup_env[++i])
	{
		if (ft_strncmp(dup_env[i], name, ft_strlen(name)) == 0)
		{
			if (dup_env[i][ft_strlen(name)] == '\0' \
					|| dup_env[i][ft_strlen(name)] == '=')
			{
				free(dup_env[i]);
				dup_env[i] = ft_strdup(cmd);
				flag = 1;
				break ;
			}
		}
	}
	if (flag == 0)
		creat_env(cmd, data);
}

void	update_env_add(char *cmd, t_data *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], cmd, ft_strlen(cmd)) == 0)
		{
			if (data->env[i][ft_strlen(cmd)] == '\0' \
					|| data->env[i][ft_strlen(cmd)] == '=')
				flag = 1;
		}
	}
	if (flag == 0)
		creat_env(cmd, data);
}

int	export_env_add(char *cmd, char end, t_data *data)
{
	char	*equal_pos;
	char	*name;

	if (end != '\0' && end != '=')
		return (1);
	equal_pos = ft_strchr(cmd, '=');
	if (equal_pos)
	{
		name = ft_substr(cmd, 0, equal_pos - cmd);
		update_env_value(cmd, name, data);
		free(name);
	}
	else
		update_env_add(cmd, data);
	return (0);
}
