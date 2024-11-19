/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:31:27 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/18 00:46:19 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	connect_head(t_data **head, char **tmp1)
{
	char	*tmp2;

	while (*head)
	{
		tmp2 = ft_strjoin(*tmp1, (*head)->str);
		free(*tmp1);
		*tmp1 = tmp2;
		*head = (*head)->next;
	}
}

void	trim_qoute(t_data **data, char **tmp3, char **env)
{
	char	*tmp;

	tmp = ft_strtrim((*data)->str, "\"");
	free((*data)->str);
	(*data)->str = tmp;
	*tmp3 = substitution_dollar((*data)->str, env);
	if (*tmp3)
	{
		free((*data)->str);
		(*data)->str = *tmp3;
	}
}

void	rotate_env_sup(t_data *data, char *tmp1, char *tmp3, char **env)
{
	if (data->type == '\"')
		trim_qoute(&data, &tmp3, env);
	else if (data->type == '\'')
	{
		tmp1 = ft_strtrim(data->str, "\'");
		free(data->str);
		data->str = tmp1;
	}
	else
	{
		tmp3 = substitution_dollar(data->str, env);
		if (tmp3)
		{
			free(data->str);
			data->str = tmp3;
		}
	}
}

char	*rotate_envstring(t_data *data, char **env)
{
	char	*tmp1;
	char	*tmp3;
	t_data	*head;

	head = data;
	tmp1 = NULL;
	tmp3 = NULL;
	while (data)
	{
		rotate_env_sup(data, tmp1, tmp3, env);
		data = data->next;
	}
	tmp1 = ft_strdup(head->str);
	head = head->next;
	connect_head(&head, &tmp1);
	return (tmp1);
}

int	here_doc_num(t_data *real)
{
	int	i;

	i = 0;
	while (real)
	{
		if (real->type == HEREDOC)
			i++;
		real = real->next;
	}
	return (i);
}
