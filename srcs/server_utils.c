/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:32:41 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 23:34:51 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	srv_addone(t_server *t_ptr)
{
	t_ptr->bytes <<= 1;
	t_ptr->bytes ^= 1;
	t_ptr->len++;
}

void	srv_addzero(t_server *t_ptr)
{
	t_ptr->bytes <<= 1;
	t_ptr->bytes ^= 0;
	t_ptr->len++;
}

void	srv_addbyte(t_server *t_ptr)
{
	if (t_ptr->bytes == 0)
		t_ptr->str[t_ptr->add++] = '\n';
	else
		t_ptr->str[t_ptr->add++] = t_ptr->bytes;
	t_ptr->add %= 4096;
	t_ptr->bytes = 0;
	t_ptr->len = 0;
}
