/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 05:46:13 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/17 16:27:30 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_originterm(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	init_env_and_exit_status(t_data *table, char **env)
{
	table->env = copy_env(env);
	set_term();
	set_sig();
}

void	init_data(t_l *new, char **env)
{
	new->to_ex = (t_data *)malloc(sizeof(t_data));
	init_env_and_exit_status(new->to_ex, env);
}

void	free_data(t_data **data)
{
	t_data	*tmp;

	while (*data)
	{
		tmp = *data;
		*data = (*data)->next;
		free(tmp->str);
		free(tmp);
	}
	free(*data);
}
