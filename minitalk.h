/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:43:45 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/08 20:36:03 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int					pid;
	char				*ch;
}				t_data;

void	signal_error(void);
void	ft_putnbr(int n);
void	ft_putchar(char c);

#endif