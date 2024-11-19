/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_chance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 05:59:36 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/18 00:50:23 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	get_arg_len(char *str, int ignore_type)
{
	int		i;
	int		st;
	int		flag_sq;
	int		flag_dq;

	str = str + skip_white_sapce(str);
	i = 0;
	st = 0;
	flag_sq = 0;
	flag_dq = 0;
	while (str[i])
	{
		st = 0;
		if (str[i] == '\'' && !flag_dq)
			flag_sq = !flag_sq;
		else if (str[i] == '\"' && !flag_sq)
			flag_dq = !flag_dq;
		if (!flag_dq && !flag_sq && is_seperater(str + i) == ignore_type)
			return (i + st);
		i++;
	}
	if (check_gal_qu(&flag_dq, &flag_sq) != 0)
		g_exit_status = 258;
	return (i);
}

t_data	*split_seperator(t_data *first)
{
	t_data	*ret;
	int		check;

	check = 0;
	ret = NULL;
	while (first)
	{
		parse2(first->str, &ret);
		if (check != 0)
			return (NULL);
		first = first->next;
	}
	return (ret);
}

t_command	*main_parse(char *line, t_l *new, char **env, int **here_doc_box)
{
	t_command	*cmd;

	new->first = NULL;
	new->head = NULL;
	new->real = NULL;
	parse(line, SPACE_, &new->first);
	new->head = split_seperator(new->first);
	if (g_exit_status == 258)
		new->head = NULL;
	new->real = push_type(new->head);
	if (g_exit_status == 258)
	{
		new_free(new);
		free(new->real);
		return (NULL);
	}
	*here_doc_box = open_here_doc(new->real, new->real->str);
	replace_check(new->real, env);
	cmd = rotate_list(new->real);
	if (cmd == NULL)
	{
		new_free(new);
		return (NULL);
	}
	return (cmd);
}

void	handle_command(t_l *new, char *line, char **env)
{
	t_command	*cmd;
	int			*hd_box;

	cmd = main_parse(line, new, env, &hd_box);
	if (cmd == NULL)
	{
		check_cmd(cmd);
		return ;
	}
	set_index(cmd);
	open_any_file(new->real, cmd, hd_box);
	if (g_exit_status == 258)
	{
		check_exit_stat(cmd, new);
		return ;
	}
	after_any_file(new, cmd);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_l			new;

	init_data(&new, env);
	while (ac && av)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line && !check_whitespace(line))
		{
			add_history(line);
			handle_command(&new, line, env);
		}
		set_term();
	}
	free_env(new.to_ex);
	exit (0);
}
