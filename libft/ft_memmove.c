/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:24:55 by suhyun            #+#    #+#             */
/*   Updated: 2023/01/04 18:34:34 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = dst;
	sp = src;
	if (dp == sp)
		return (dst);
	if (dst < src)
		ft_memcpy(dp, sp, len);
	else
	{
		while (len--)
			*(dp + len) = *(sp + len);
	}
	return (dst);
}
