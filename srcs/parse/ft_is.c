/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:51:40 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/17 14:30:37 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	ft_isdollar(char s)
{
	if (s == '$')
		return (1);
	return (0);
}

int	ft_isspace(char s)
{
	if (s == ' ')
		return (1);
	return (0);
}

int	is_seperater(char *c)
{
	if (!ft_strncmp(c, ">>", 2))
		return (1);
	else if (!ft_strncmp(c, "<<", 2))
		return (1);
	else if (!ft_strncmp(c, ">", 1))
		return (1);
	else if (!ft_strncmp(c, "<", 1))
		return (1);
	else if (!ft_strncmp(c, "|", 1))
		return (1);
	else if (!ft_strncmp(c, "\"", 1))
		return (2);
	else if (!ft_strncmp(c, "\'", 1))
		return (2);
	if (!ft_strncmp(c, " ", 1) || !ft_strncmp(c, "	", 1))
		return (5);
	return (0);
}

int	is_seperater2(char *c)
{
	if (!ft_strncmp(c, ">>", 2))
		return (OUTAPPEN);
	if (!ft_strncmp(c, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(c, ">", 1))
		return (OUT);
	if (!ft_strncmp(c, "<", 1))
		return (IN);
	if (!ft_strncmp(c, "|", 1))
		return (PIPE_);
	return (-1);
}

void	error_exit(char *str, int num)
{
	printf("%s\n", str);
	exit(num);
}
