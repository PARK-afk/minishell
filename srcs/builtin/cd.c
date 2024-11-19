/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:25:41 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/12 03:46:49 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	ft_change_pwd(char *key, char *new_val, char **env)
{
	int		i;
	int		key_len;
	char	*env_val;
	char	*slash;

	i = -1;
	key_len = ft_strlen(key);
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, strlen(key)) == 0 && \
				env[i][key_len] == '=')
		{
			slash = ft_strjoin(key, "=");
			env_val = ft_strjoin(slash, new_val);
			free(env[i]);
			env[i] = NULL;
			env[i] = env_val;
			free(slash);
			break ;
		}
	}
}

int	cd_err(char *err_msg, char **cur, char **new_path)
{
	ft_putstr_fd("minishell: ", 2);
	if (err_msg[0] == '~' && err_msg[1] == '/')
		perror(*new_path);
	else
		perror(err_msg);
	if (cur && *cur)
		free(*cur);
	if (new_path && *new_path)
		free(*new_path);
	return (1);
}

char	*find_path(char *path, char *cmd, char **env)
{
	char	*ret;
	char	*slash;

	if (cmd == NULL)
		return (ft_strdup(ft_getenv("HOME", env)));
	else if (cmd[0] == '~')
		return (ft_strjoin(ft_getenv("HOME", env), &cmd[1]));
	else if (cmd[0] == '/')
		return (ft_strdup(cmd));
	else if (cmd[0] == '-')
		return (ft_strdup(ft_getenv("OLDPWD", env)));
	else
	{
		slash = ft_strjoin(path, "/");
		ret = ft_strjoin(slash, cmd);
		free(slash);
		return (ret);
	}
	return (NULL);
}

int	ft_cd(t_command *dir_name, char ***env)
{
	char	*cur;
	char	*pwd;
	char	*new_path;

	cur = getcwd(NULL, 0);
	new_path = find_path(cur, dir_name->cmd[1], (*env));
	if (access(new_path, F_OK) != 0)
		return (cd_err(dir_name->cmd[1], &cur, &new_path));
	if (chdir(new_path) != 0)
		return (cd_err(dir_name->cmd[1], &cur, &new_path));
	ft_change_pwd("OLDPWD", cur, *env);
	pwd = getcwd(NULL, 0);
	ft_change_pwd("PWD", pwd, *env);
	free(cur);
	free(pwd);
	free(new_path);
	return (0);
}
