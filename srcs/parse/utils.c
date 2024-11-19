/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 03:44:27 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/18 00:53:18 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	check_qu(int sq, int dq, char *filename)
{
	if (sq || dq)
	{
		free(filename);
		g_exit_status = 258;
		return (-1);
	}
	return (0);
}

void	chec_how_qu(int *dq_flag, int *sq_flag, char *filename, int *i)
{
	if (filename[*i] == '\'' && !*dq_flag)
		*sq_flag = !*sq_flag;
	else if (filename[*i] == '\"' && !*sq_flag)
		*dq_flag = !*dq_flag;
}

int	check_gal_qu(int *flag_dq, int *flag_sq)
{
	if (*flag_dq || *flag_sq)
	{
		g_exit_status = 258;
		return (-1);
	}
	return (0);
}

int	skip_white_sapce(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == 32)
		i++;
	return (i);
}

int	check_dollar(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '$')
			return (1);
	return (0);
}
