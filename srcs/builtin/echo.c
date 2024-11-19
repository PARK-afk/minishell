/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:25:33 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/10 01:30:26 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	print_cmd(char **cmd, int i);

int	ft_echo(char **cmd)
{
	int	i;
	int	j;
	int	n_option;

	i = 1;
	n_option = false;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_cmd(cmd, i);
	if (n_option == false)
		printf("\n");
	return (0);
}

void	print_cmd(char **cmd, int i)
{
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
}
