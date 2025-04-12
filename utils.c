/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmtioui <hmtioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 21:13:53 by hmtioui           #+#    #+#             */
/*   Updated: 2025/03/31 00:01:10 by hmtioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(int n)
{
	long	nb;
	size_t	i;
	char	nbr[11];

	nb = n;
	if (nb == 0)
		write(1, "0", 1);
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	i = 0;
	while (nb)
	{
		nbr[i] = nb % 10 + 48;
		nb /= 10;
		i++;
	}
	while (i > 0)
		write(1, &nbr[--i], 1);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	m;

	n = 0;
	i = 0;
	m = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		n = n * 10 + str[i++] - 48;
	return (n * m);
}

int	checkletters(const char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (pid[i] < '0' || pid[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	print_error(void)
{
	ft_putstr("\033[1;31mWrong PID ❌\033[0m\n");
	exit(1);
}
