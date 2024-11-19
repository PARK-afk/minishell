/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:24:22 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/10 01:59:41 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	export_error(char *s, int *ret)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*ret = 1;
}

int	check_export_valid(char **cmd, t_data *data)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		if (cmd[i][0] == '=')
		{
			export_error(cmd[i], &ret);
			continue ;
		}
		while (cmd[i][j] && cmd[i][j] != '=')
		{
			if (!(ft_isalpha(cmd[i][0]) || cmd[i][j] == '_'))
			{
				export_error(cmd[i], &ret);
				break ;
			}
			j++;
		}
		ret = export_env_add(cmd[i], cmd[i][j], data);
	}
	return (ret);
}

int	ft_export(char **cmd, t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	if (cmd[1] == NULL)
		ret = export_print(data->env);
	else
		ret = check_export_valid(cmd, data);
	return (ret);
}
