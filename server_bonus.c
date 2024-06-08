/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:48:42 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/08 19:57:44 by ibouram          ###   ########.fr       */
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

void	initialization(t_data *data)
{
	data->byte = 0;
	data->bit = 0;
	data->i = 0;
	data->len = 1;
}

void	handler(int sig, siginfo_t *info, void *content)
{
	static t_data			data;

	initialization(&data);
	(void)content;
	if (data.pid != info->si_pid)
	{
		data.pid = info->si_pid;
		data.bit = 0;
		data.byte = 0;
		data.i = 0;
		data.len = 1;
	}
	data.byte = (data.byte << 1) + (sig == SIGUSR2);
	data.bit++;
	if (data.bit == 8)
	{
		if (data.byte == 0)
		{
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
		}
		ft_unicode(data.byte, &data.i, &data.len, &data.ch);
		data.bit = 0;
		data.byte = 0;
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
