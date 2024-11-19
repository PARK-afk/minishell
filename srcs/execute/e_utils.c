/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:27:17 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/15 23:58:32 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	cmd_list_free(t_command **cmd)
{
	t_command	*tmp;

	while (*cmd)
	{
		tmp = (*cmd);
		tmp->infile = 0;
		tmp->outfile = 0;
		free_arr(tmp->cmd);
		*cmd = (*cmd)->next;
		free(tmp);
	}
	free(*cmd);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	data_free(t_data *data, t_command *cmd)
{
	cmd_list_free(&cmd);
	free_arr(data->env);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*equal;
	char	*envp;

	equal = ft_strjoin(name, "=");
	envp = NULL;
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], equal, ft_strlen(equal)) == 0)
		{
			while (env[i][j] && env[i][j] != '=')
				j++;
			envp = &env[i][j + 1];
			break ;
		}
		i++;
	}
	free(equal);
	return (envp);
}

int	ft_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
