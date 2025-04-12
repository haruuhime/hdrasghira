/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmtioui <hmtioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:13:42 by hmtioui           #+#    #+#             */
/*   Updated: 2025/04/13 00:20:48 by hmtioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_flag = 0;

static void	server_handler(int sigusr, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sigusr == SIGUSR1)
		g_flag = 1;
	else if (sigusr == SIGUSR2)
	{
		ft_putstr("\033[1;32mThe message is received successfully✅\033[0m\n");
		exit(0);
	}
}

static void	handler(char c, int pid)
{
	int				bits;
	unsigned char	temp;

	temp = c;
	bits = 8;
	while (bits--)
	{
		g_flag = 0;
		if (temp >> bits & 1)
		{
			if (kill(pid, SIGUSR1) < 0)
				print_error();
		}
		else if (kill(pid, SIGUSR2) < 0)
			print_error();
		while (!g_flag)
			pause();
	}
	usleep(90);
}

static void	sending(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
		handler(str[i++], pid);
	handler('\0', pid);
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_putstr("\033[1;31mPlease enter 3 arguments 🐌\033[0m");
		return (1);
	}
	sa.sa_sigaction = &server_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	pid = ft_atoi(av[1]);
	if (ft_atoi(av[1]) <= 0 || checkletters(av[1]))
		print_error();
	sending(av[2], pid);
	return (0);
}
