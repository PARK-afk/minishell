/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:24:11 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/10 01:30:32 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	str_digit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	err_exit(char *s)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required", STDERR_FILENO);
	return (255);
}

int	ft_exit(char **str)
{
	int	exit_val;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (str[1] && str[2])
	{
		ft_putendl_fd("minishell: exit: too many argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!str[1])
		exit_val = 0;
	else if (str_digit(str[1]))
		exit_val = ft_atoi(str[1]) % 256;
	else
		exit_val = err_exit(str[1]);
	exit(exit_val);
}
