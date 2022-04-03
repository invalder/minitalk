/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:01:32 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 00:37:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE

# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>

typedef struct s_client
{
	int	sending;
	int	tik;
}	t_client;

typedef struct s_server
{
	size_t	len;
	size_t	bytes;
	char	str[4096];
	int		cur;
	int		add;
}	t_server;

void	srv_resbit(int c_pid);
void	srv_resbyte(int c_pid);
void	init_srv(t_server *t_ptr);
void	srv_addone(t_server *t_ptr);
void	srv_addzero(t_server *t_ptr);
void	srv_addbyte(t_server *t_ptr);

void	ft_sendbyte(char *pbuf, int s_pid, t_client *t_cptr);
void	ft_sendbit(char b, int s_pid, t_client *t_cptr);
void	ft_biterr(t_client *t_cptr);
char	*ft_getbyte(char *ptr);

#endif
