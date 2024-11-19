/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:01:51 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/17 20:10:08 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	skip_quote(t_data **mom, char *str, int *i)
{
	char	sep;
	int		st;
	int		en;
	char	*tmp;

	st = *i;
	sep = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != sep)
		(*i)++;
	en = *i;
	if (str[*i] == '\0')
		return ;
	tmp = ft_substr(str + st, 0, en - st + 1);
	push(mom, tmp, (int)sep);
	free(tmp);
	(*i)++;
}

void	handle_unquoted_segment(t_data **mom, char *str, int *i)
{
	int		st;
	int		en;
	char	*tmp;

	st = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	en = *i;
	tmp = ft_substr(str + st, 0, en - st);
	push(mom, tmp, NOTQ);
	free(tmp);
}

char	*remove_quote(char *str, char **env)
{
	int		i;
	t_data	*mom;
	char	*tmp;

	i = 0;
	mom = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quote(&mom, str, &i);
		else
			handle_unquoted_segment(&mom, str, &i);
	}
	tmp = rotate_envstring(mom, env);
	free_data(&mom);
	return (tmp);
}

void	replace_check(t_data *real, char **env)
{
	char	*tmp;

	while (real)
	{
		if (real->type != PIPE_)
		{
			tmp = remove_quote(real->str, env);
			if (tmp)
			{
				free(real->str);
				real->str = tmp;
			}
			else
				free(tmp);
		}
		real = real->next;
	}
}
