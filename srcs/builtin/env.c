/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:25:01 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/10 01:30:28 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_equal_sign(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
