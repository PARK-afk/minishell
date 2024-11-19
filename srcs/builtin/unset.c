/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:24:45 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/12 03:46:13 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	unset_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] == '_' || ft_isalpha(str[i])))
		{
			ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	remove_cmd(char **cmd, char **env)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[++i])
	{
		j = -1;
		ret += unset_error(cmd[i]);
		while (env[++j])
		{
			if (ft_strncmp(env[j], cmd[i], ft_strlen(cmd[i])) == 0 && \
				(env[j][ft_strlen(cmd[i])] == '\0' || \
					env[j][ft_strlen(cmd[i])] == '='))
			{
				free(env[j]);
				env[j] = ft_strdup("");
				break ;
			}
		}
	}
	if (ret > 0)
		return (1);
	return (0);
}

char	**make_deleted_env(char **env)
{
	char	**ret;
	int		env_len;
	int		i;

	i = 0;
	env_len = ft_env_len(env);
	ret = (char **)ft_calloc(sizeof(char *), env_len + 1);
	if (!ret)
		return (NULL);
	ret[env_len] = NULL;
	env_len = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] != '\0')
		{
			ret[env_len] = ft_strdup(env[i]);
			env_len++;
		}
		i++;
	}
	return (ret);
}

char	**cp_env(char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i] = NULL;
	return (tmp);
}

int	ft_unset(char **del, t_data *data)
{
	char	**new_env;
	char	**copied_env;
	int		ret;

	if (!del[1])
		return (EXIT_SUCCESS);
	copied_env = cp_env(data->env);
	if (copied_env == NULL)
		return (EXIT_FAILURE);
	ret = remove_cmd(del, copied_env);
	new_env = make_deleted_env(copied_env);
	if (new_env == NULL)
	{
		free_arr(copied_env);
		return (EXIT_FAILURE);
	}
	free_arr(copied_env);
	free_arr(data->env);
	data->env = new_env;
	return (ret);
}
