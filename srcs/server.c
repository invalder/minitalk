/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:01:45 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 01:08:25 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	g_srv;

static void	sigusr_handle(int signo, siginfo_t *info, void *other);

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID = %d.\n", getpid());
	usleep(10);
	sa.sa_sigaction = sigusr_handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_srv.cur = 0;
	g_srv.add = 0;
	while (1)
	{
		if (g_srv.cur != g_srv.add)
		{
			write(1, &g_srv.str[g_srv.cur++], 1);
			g_srv.cur %= 4096;
			usleep(10);
		}
	}
	exit(0);
}

static void	sigusr_handle(int signo, siginfo_t *info, void *other)
{
	static int	c_pid = 0;

	(void)other;
	if (!c_pid)
	{
		c_pid = info->si_pid;
		init_srv(&g_srv);
	}
	if (signo == SIGUSR1)
	{
		srv_addzero(&g_srv);
		srv_resbit(c_pid);
	}
	if (signo == SIGUSR2)
	{
		srv_addone(&g_srv);
		srv_resbit(c_pid);
	}
	if (g_srv.len > 7)
	{
		srv_addbyte(&g_srv);
		srv_resbyte(c_pid);
		c_pid = 0;
	}
}

void	srv_resbit(int c_pid)
{
	if (c_pid)
		kill(c_pid, SIGUSR1);
}

void	srv_resbyte(int c_pid)
{
	if (c_pid)
		kill(c_pid, SIGUSR2);
}

void	init_srv(t_server *t_ptr)
{
	t_ptr->bytes = 0;
	t_ptr->len = 0;
}
