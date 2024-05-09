/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:12:45 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/06 13:36:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_signal(int server_pid, char *message)
{
	int	null_bit_count;

	while (*message)
	{
		send_char_bits(server_pid, *message);
		message++;
	}
	null_bit_count = 0;
	while (null_bit_count < 8)
	{
		kill(server_pid, SIGUSR2);
		usleep(150);
		null_bit_count++;
	}
}

void	send_char_bits(int server_pid, char char_to_send)
{
	int	bit_index;

	bit_index = 0;
	while (bit_index < 8)
	{
		if (char_to_send & (0b10000000 >> bit_index))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		bit_index++;
		usleep(150);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Usage Error: ./client <Server PID> <Message>\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		send_signal(ft_atoi(argv[1]), argv[2]);
	}
	return (0);
}
