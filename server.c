/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmtioui <hmtioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:13:50 by hmtioui           #+#    #+#             */
/*   Updated: 2025/04/13 00:33:36 by hmtioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	printchar(int *bits, char *c, int current_pid)
{
	if (*c == '\0')
		kill(current_pid, SIGUSR2);
	ft_putstr(c);
	*c = 0;
	*bits = 0;
}

static void	handlerbits(int sigusr, siginfo_t *info, void *context)
{
	static int	bits;
	static char	c;
	static int	current_pid;
	static int	client_pid;

	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		bits = 0;
		c = 0;
		client_pid = current_pid;
	}
	(void)context;
	c <<= 1;
	if (sigusr == SIGUSR1)
		c += 1;
	bits++;
	if (bits == 8)
		printchar(&bits, &c, current_pid);
	usleep(90);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &handlerbits;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
