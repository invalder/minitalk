/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:06:30 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 01:06:32 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sendbyte(char *pbuf, int s_pid, t_client *t_cptr)
{
	while (*pbuf)
	{
		if (t_cptr->sending == 0)
		{
			ft_sendbit(*pbuf, s_pid, t_cptr);
			usleep(10);
			pbuf++;
		}
		else
		{
			ft_biterr(t_cptr);
			usleep(10);
			continue ;
		}
	}
}

void	ft_sendbit(char b, int s_pid, t_client *t_cptr)
{
	t_cptr->sending = 1;
	if (b == '0')
	{
		if (kill(s_pid, SIGUSR1) == -1)
		{
			write(1, "Error while sending 0\n", 23);
			exit(1);
		}
	}
	else if (b == '1')
	{
		if (kill(s_pid, SIGUSR2) == -1)
		{
			write(1, "Error while sending 1\n", 23);
			exit(1);
		}
	}
}

void	ft_biterr(t_client *t_cptr)
{
	if (t_cptr->sending)
	{
		t_cptr->tik++;
	}
	else
		t_cptr->tik = 0;
	if (t_cptr->tik == 100000)
	{
		write(1, "Bit Error\n", 11);
		t_cptr->sending = 0;
		t_cptr->tik = 0;
	}
}

char	*ft_getbyte(char *ptr)
{
	char	*buf;
	char	*width_buff;

	buf = NULL;
	buf = ft_print_nbru_b((unsigned char)*ptr, buf, 2, 0);
	if (!buf)
		exit (1);
	if (buf && ft_strlen(buf) != 8)
	{
		width_buff = ft_mycalloc(1, 8 - ft_strlen(buf) + 1, '0');
		if (!width_buff)
			exit (1);
		buf = ft_mystrjoin(width_buff, buf, 1, 1);
		if (!buf)
			exit (1);
	}
	usleep(100);
	return (buf);
}
