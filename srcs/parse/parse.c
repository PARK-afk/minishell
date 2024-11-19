/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:58:46 by junsepar          #+#    #+#             */
/*   Updated: 2023/09/18 00:46:45 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	parse(char *str, int ignore_type, t_data **mydata)
{
	int		i;
	char	*tmp;
	int		len;
	int		st;

	i = 0;
	st = 0;
	while (str[i])
	{
		if (is_seperater(str + i) != ignore_type)
		{
			st = i;
			i += skip_white_sapce(str + i);
			len = get_arg_len(str + st, ignore_type);
			tmp = ft_substr(str + i, 0, len);
			push(mydata, tmp, 0);
			i += len;
			if (str[i] == 32)
				i += skip_white_sapce(str + i);
			free(tmp);
		}
		else
			i++;
	}
	free(str);
}

char	*update_line(int *i, char *str, int *type)
{
	int		st;
	int		len;
	char	*tmp;

	st = *i;
	*type = is_seperater2(str + *i);
	len = get_arg_len(str + st, 1);
	tmp = ft_substr(str + *i, 0, len);
	*i += len;
	return (tmp);
}

char	*update_line2(int *i, char *str)
{
	int		st;
	char	*tmp;
	int		len;

	st = *i;
	len = get_arg_len(str + st, 0);
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
		len = 2;
	else if (str[st] == '|' || str[st] == '<' || str[st] == '>')
		len = 1;
	tmp = ft_substr(str + *i, 0, len);
	*i += len;
	return (tmp);
}

void	check_quote_flag(int *flag_sq, int *flag_dq, char *str, int i)
{
	if (str[i] == '\'' && !*flag_dq)
		*flag_sq = !*flag_sq;
	if (str[i] == '\"' && !*flag_sq)
		*flag_dq = !*flag_dq;
}

void	parse2(char *str, t_data **newdata)
{
	int		i;
	int		type;
	int		flag_sq;
	int		flag_dq;
	char	*tmp;

	i = 0;
	flag_sq = 0;
	flag_dq = 0;
	while (str && str[i])
	{
		check_quote_flag(&flag_sq, &flag_dq, str, i);
		if ((!flag_dq && !flag_sq) && (is_seperater(str + i) != 1))
		{
			tmp = update_line(&i, str, &type);
			push(newdata, tmp, type);
			free(tmp);
		}
		else if ((!flag_dq && !flag_sq))
		{
			tmp = update_line2(&i, str);
			push(newdata, tmp, -5);
			free(tmp);
		}
	}
}
