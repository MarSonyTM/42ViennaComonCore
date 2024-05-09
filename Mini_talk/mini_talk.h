/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:34:48 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/06 17:40:54 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# include "./Libft/libft.h"
# include <signal.h>

# define BUFFER_SIZE 100000

void	send_char_bits(int server_pid, char char_to_send);
void	send_signal(int server_pid, char *message);
int		handle_buffer(unsigned char character,
			char *buffer, int buffer_index);
int		process_signal(int signal_type,
			unsigned char *character, int *bit_count);

#endif