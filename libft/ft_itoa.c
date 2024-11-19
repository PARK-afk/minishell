/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:07:47 by suhyun            #+#    #+#             */
/*   Updated: 2023/01/04 21:56:58 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_len(int n);

char	*ft_itoa(int n)
{
	char		*result;
	int			len;
	long long	num;

	num = (long long)n;
	len = digit_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (num < 0)
		num *= -1;
	if (num == 0)
		result[0] = '0';
	result[len] = '\0';
	while (len-- > 0)
	{
		result[len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

static int	digit_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += 1;
	if (n < 0)
	{
		n *= -1;
		len += 1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
