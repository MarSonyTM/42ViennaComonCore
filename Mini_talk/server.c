/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:15:52 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/06 13:40:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	receive_signal(int signal_type)
{
	static int				bit_count = 0;
	static unsigned char	character = 0;
	static char				buffer[BUFFER_SIZE];
	static int				buffer_index = 0;
	int						is_complete_byte;

	is_complete_byte = process_signal(signal_type, &character, &bit_count);
	if (is_complete_byte)
	{
		buffer_index = handle_buffer(character, buffer, buffer_index);
		bit_count = 0;
		character = 0;
	}
}

int	process_signal(int signal_type, unsigned char *character, int *bit_count)
{
	if (signal_type == SIGUSR2)
		*character = *character << 1;
	else if (signal_type == SIGUSR1)
		*character = (*character << 1) | 1;
	(*bit_count)++;
	return (*bit_count == 8);
}

int	handle_buffer(unsigned char character, char *buffer, int buffer_index)
{
	buffer[buffer_index++] = character;
	if (character == '\0')
	{
		ft_printf("%s\n", buffer);
		buffer_index = 0;
	}
	else if (buffer_index == BUFFER_SIZE - 1)
	{
		buffer[buffer_index] = '\0';
		ft_printf("%s", buffer);
		buffer_index = 0;
	}
	return (buffer_index);
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	while (1)
	{
		pause();
	}
	return (0);
}
