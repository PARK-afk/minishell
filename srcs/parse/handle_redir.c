/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhyun <suhyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:56:05 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/17 14:47:14 by suhyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

void	handle_append(t_data **mydata, t_data **real)
{
	if (!(*mydata)->next)
	{
		g_exit_status = 258;
		return ;
	}
	push(real, (*mydata)->next->str, OUTAPPEN);
	(*mydata) = (*mydata)->next;
}

void	handle_heredoc(t_data **mydata, t_data **real)
{
	if (!(*mydata)->next)
	{
		g_exit_status = 258;
		return ;
	}
	push(real, (*mydata)->next->str, HEREDOC);
	(*mydata) = (*mydata)->next;
}

void	handle_right_redirect(t_data **mydata, t_data **real)
{
	if (!(*mydata)->next)
	{
		g_exit_status = 258;
		return ;
	}
	push(real, (*mydata)->next->str, OUT);
	(*mydata) = (*mydata)->next;
}

void	handle_left_redirect(t_data **mydata, t_data **real)
{
	if (!(*mydata)->next)
	{
		g_exit_status = 258;
		return ;
	}
	else
	{
		push(real, (*mydata)->next->str, IN);
		(*mydata) = (*mydata)->next;
	}
}
