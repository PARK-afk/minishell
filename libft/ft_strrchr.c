/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:20:32 by suhyun            #+#    #+#             */
/*   Updated: 2023/01/04 21:34:56 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		s_len;

	tmp = (char *)s;
	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (tmp[s_len] == (unsigned char)c)
			return (&tmp[s_len]);
		s_len--;
	}
	return (NULL);
}
