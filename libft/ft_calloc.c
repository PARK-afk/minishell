/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 02:50:38 by suhyun            #+#    #+#             */
/*   Updated: 2023/08/17 10:19:13 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		len;
	void	*tmp;

	if (count <= 0 || size <= 0)
		len = 1;
	else
		len = count * size;
	tmp = malloc(len);
	if (!tmp)
		_("malloc");
	ft_memset(tmp, 0, len);
	return (tmp);
}
