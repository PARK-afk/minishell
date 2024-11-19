/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:55:04 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/16 04:50:03 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	count_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data)
	{
		if (data->type == ARG)
			i++;
		if (data->type == PIPE_)
			break ;
		data = data->next;
	}
	return (i);
}

char	**make_cmd(t_data *data)
{
	int		cmd_size;
	char	**tmp;
	int		i;

	cmd_size = count_cmd(data);
	if (cmd_size == 0)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	i = 0;
	while (data)
	{
		if (data->type == PIPE_)
			break ;
		else if (data->type == ARG)
		{
			tmp[i] = ft_strdup(data->str);
			i++;
		}
		data = data->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	print_cmd1(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			printf("%s ", cmd->cmd[i]);
			i++;
		}
		printf("infile : %d, outfile : %d", cmd->infile, cmd->outfile);
		printf("\n");
		cmd = cmd->next;
	}
}

void	free_cmd(t_command *data)
{
	char	**cmd;
	int		i;

	cmd = data->cmd;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
