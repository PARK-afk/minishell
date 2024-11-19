/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:36:32 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/17 14:39:21 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

char	**copy_env(char **env)
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

void	sort_ascii(char **env)
{
	int		i;
	int		j;
	char	**sorted_env;

	sorted_env = copy_env(env);
	i = 0;
	while (sorted_env[i])
	{
		j = 0;
		printf("delcare -x ");
		while (sorted_env[i][j] != '\0' && sorted_env[i][j] != '=')
		{
			printf("%c", sorted_env[i][j]);
			j++;
		}
		if (sorted_env[i][j] == '=')
			printf("=\"%s\"", &sorted_env[i][j + 1]);
		printf("\n");
		i++;
	}
}

int	export_print(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**copied_env;

	copied_env = copy_env(env);
	i = 0;
	while (copied_env[i])
	{
		j = i + 1;
		while (copied_env[j])
		{
			if (ft_strcmp(copied_env[i], copied_env[j]) > 0)
			{
				tmp = copied_env[i];
				copied_env[i] = copied_env[j];
				copied_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	sort_ascii(copied_env);
	free_arr(copied_env);
	return (0);
}
