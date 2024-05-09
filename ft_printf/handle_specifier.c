/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:53 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/25 14:36:45 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_specifier(char specifier, va_list args, int *char_count)
{
	if (specifier == 'c')
		handle_char(args, char_count);
	else if (specifier == 's')
		handle_string(args, char_count);
	else if (specifier == 'p')
		handle_pointer(args, char_count);
	else if (specifier == 'd' || specifier == 'i')
		handle_int(args, char_count);
	else if (specifier == 'u')
		handle_uint(args, char_count);
	else if (specifier == 'x')
		handle_hex_lower(args, char_count);
	else if (specifier == 'X')
		handle_hex_upper(args, char_count);
	else if (specifier == '%')
		handle_percent(char_count);
}
