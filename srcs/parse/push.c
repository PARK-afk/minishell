/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:53:47 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/18 00:11:49 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	push(t_data **data, char *str, int type)
{
	t_data	*tmp;
	t_data	*head;

	tmp = *data;
	if (tmp == NULL)
	{
		tmp = (t_data *)malloc(sizeof(t_data));
		tmp->str = ft_strdup(str);
		tmp->type = type;
		tmp->next = NULL;
		*data = tmp;
	}
	else
	{
		head = *data;
		while (head->next)
			head = head->next;
		tmp = (t_data *)malloc(sizeof(t_data));
		tmp->str = ft_strdup(str);
		tmp->type = type;
		tmp->next = NULL;
		head->next = tmp;
	}
}

void	sup_pipe(t_data *mydata, t_data *real)
{
	if (!mydata->next)
	{
		g_exit_status = 258;
		return ;
	}
	else
		push(&real, NULL, PIPE_);
}

t_data	*push_type(t_data *mydata)
{
	t_data	*real;

	real = NULL;
	while (mydata)
	{
		if (!ft_strncmp(mydata->str, ">>", 2))
			handle_append(&mydata, &real);
		else if (!ft_strncmp(mydata->str, "<<", 2))
			handle_heredoc(&mydata, &real);
		else if (!ft_strncmp(mydata->str, ">", 1))
			handle_right_redirect(&mydata, &real);
		else if (!ft_strncmp(mydata->str, "<", 1))
			handle_left_redirect(&mydata, &real);
		else if (!ft_strncmp(mydata->str, "|", 1))
			sup_pipe(mydata, real);
		else
			push(&real, mydata->str, ARG);
		if (g_exit_status == 258)
			return (NULL);
		mydata = mydata->next;
	}
	return (real);
}

void	push2(t_command **data, char **cmd, int infile, int outfile)
{
	t_command	*tmp;
	t_command	*head;

	tmp = *data;
	if (tmp == NULL)
	{
		tmp = (t_command *)malloc(sizeof(t_command));
		tmp->cmd = cmd;
		tmp->infile = infile;
		tmp->outfile = outfile;
		tmp->next = NULL;
		*data = tmp;
	}
	else
	{
		head = *data;
		while (head->next)
			head = head->next;
		tmp = (t_command *)malloc(sizeof(t_command));
		tmp->cmd = cmd;
		tmp->infile = infile;
		tmp->outfile = outfile;
		tmp->next = NULL;
		head->next = tmp;
	}
}

void	set_index(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd->cmd_index = i;
		cmd = cmd->next;
		i++;
	}
}
