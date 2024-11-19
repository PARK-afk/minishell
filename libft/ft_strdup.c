/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 04:02:10 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/15 23:01:25 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*tmp;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	tmp = (char *)malloc((sizeof(char) * len) + 1);
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	while (--len >= 0)
		tmp[len] = s1[len];
	return (tmp);
}
