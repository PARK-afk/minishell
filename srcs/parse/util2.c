/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:58:42 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/17 16:21:37 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	check_exit_stat(t_command *cmd, t_l *new)
{
	g_exit_status = 0;
	cmd_list_free(&cmd);
	free_data(&new->real);
	printf("minishell $ : syntax error\n");
}

void	check_cmd(t_command *cmd)
{
	cmd_list_free(&cmd);
	g_exit_status = 0;
	printf("minishell $ : syntax error\n");
}

void	new_free(t_l *new)
{
	free_data(&new->first);
	free_data(&new->head);
}

void	after_any_file(t_l *new, t_command *cmd)
{
	new_free(new);
	execute(new->to_ex, cmd);
	free_data(&new->real);
	cmd_list_free(&cmd);
}

int	check_whitespace(const char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}
