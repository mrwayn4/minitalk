/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:48:42 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/08 21:01:34 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_unicode(unsigned char byte, int *i, int *len, char **ch)
{
	if (byte > 192)
		*len = 1 + (byte >= 192) + (byte >= 224) + (byte >= 240);
	if (*i == 0)
	{
		*ch = malloc(*len + 1);
		if (!*ch)
			return ;
	}
	if (*i < *len)
		(*ch)[(*i)++] = byte;
	if (*i == *len)
	{
		(*ch)[*i] = 0;
		write(1, *ch, *len);
		free(*ch);
		*i = 0;
		*len = 1;
	}
}

void	handler(int sig, siginfo_t *info, void *content)
{
	static char				bit = 0;
	static unsigned char	byte = 0;
	static int				i = 0;
	static int				len = 1;
	static t_data			data;

	(void)content;
	if (data.pid != info->si_pid)
	{
		data.pid = info->si_pid;
		(1) && (byte = 0, bit = 0, i = 0, len = 1);
	}
	byte = (byte << 1) + (sig == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		if (byte == 0)
		{
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
		}
		ft_unicode(byte, &i, &len, &data.ch);
		(1) && (byte = 0, bit = 0);
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
