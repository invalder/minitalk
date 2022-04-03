/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:01:51 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 01:07:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_cl;
static void	sigusr_handle(int signo, siginfo_t *info, void *other);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*ptr;
	char				*buf;
	int					s_pid;

	if (argc != 3)
		exit(1);
	ptr = argv[2];
	s_pid = ft_atoi(argv[1]);
	sa.sa_sigaction = sigusr_handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_cl.tik = 0;
	g_cl.sending = 0;
	while (ptr <= (argv[2] + ft_strlen(argv[2])))
	{
		buf = ft_getbyte(ptr);
		ft_sendbyte(buf, s_pid, &g_cl);
		free(buf);
		buf = NULL;
		ptr++;
		usleep(10);
	}
}

static void	sigusr_handle(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	if (signo == SIGUSR1)
		g_cl.sending = 0;
	else if (signo == SIGUSR2)
	{
		g_cl.sending = 0;
	}
	usleep(10);
}
