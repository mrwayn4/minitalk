/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:00:21 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/08 18:38:14 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_error(void)
{
	write(1, "Invalid PID\n", 13);
	exit(0);
}

int	valid_arg(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	total;

	sign = 1;
	total = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - '0');
		str++;
	}
	return (total * sign);
}

void	ft_send_sig(int pid, char ch)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((ch & 128) == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				signal_error();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				signal_error();
		}
		ch <<= 1;
		usleep(400);
		bit++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac != 3)
	{
		write(1, "Usage: ./client [pid] [message]\n", 33);
		return (1);
	}
	if (!valid_arg(av[1]))
	{
		write(1, "Usage: ./client [pid] [message]\n", 33);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		signal_error(); 
	while (av[2][i] != '\0')
	{
		ft_send_sig(pid, av[2][i]);
		i++;
	}
	ft_send_sig(pid, '\0');
	return (0);
}
