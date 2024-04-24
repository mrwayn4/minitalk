/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:01:04 by ibouram           #+#    #+#             */
/*   Updated: 2024/04/03 01:08:33 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	handler(int sig, siginfo_t *info, void *content)
{
	static char	bit;
	static char	byte;
	static int	pid;

	(void)content;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		bit = 0;
		byte = 0;
	}
	byte = (byte << 1) + (sig == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		write(1, &byte, 1);
		if (!byte)
			write(1, "\n", 1);
		bit = 0;
		byte = 0;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	to_do;

	(void)av;
	if (ac > 1)
	{
		write(1, "input error\n", 13);
		return (0);
	}
	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	to_do.sa_sigaction = handler;
	sigemptyset(&to_do.sa_mask);
	to_do.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &to_do, 0);
		sigaction(SIGUSR2, &to_do, 0);
		pause();
	}
}
