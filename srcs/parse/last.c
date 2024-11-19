/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:53:01 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/17 16:04:17 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

char	*target_change(char *s, char **env)
{
	int		i;
	int		len;
	char	*ret;

	ret = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0 && \
				env[i][ft_strlen(s)] == '=')
		{
			len = is_equal_sign(env[i]);
			while (env[i][len] != '\0')
				len++;
			ret = ft_substr(env[i], is_equal_sign(env[i]), len);
		}
		else if (*(s + 1) == '$')
			return (NULL);
	}
	return (ret);
}

char	*substitution_dollar(char *line, char **env)
{
	char	*target;
	int		end;
	int		i;
	char	*change;

	i = -1;
	change = NULL;
	while (line[++i] && ft_isdollar(line[i]))
	{
		if (line[i + 1] == '?')
			return (ft_itoa(g_exit_status));
		else
		{
			end = i + 1;
			while (line[end] && !(ft_isspace(line[end]) || line[end] == '\0'))
				end++;
			target = ft_substr(line, ++i, end);
			change = target_change(target, env);
			free(target);
		}
	}
	return (change);
}

int	get_cmd_cnt(t_data *head)
{
	int		i;

	i = 1;
	while (head)
	{
		if (head->type == PIPE_)
			i++;
		head = head->next;
	}
	return (i);
}

t_command	*rotate_list(t_data *data)
{
	char		**tmp;
	int			num_of_cmd;
	t_command	*com;

	com = NULL;
	num_of_cmd = get_cmd_cnt(data);
	while (num_of_cmd-- > 0)
	{
		tmp = make_cmd(data);
		while (data)
		{
			if (data->type == PIPE_)
			{
				data = data->next;
				break ;
			}
			data = data->next;
		}
		push2(&com, tmp, 0, 1);
	}
	return (com);
}

void	free_env(t_data *data)
{
	char	**env;
	int		i;

	env = data->env;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
