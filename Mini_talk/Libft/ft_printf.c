/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:56:41 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/05 11:26:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		char_count;
	int		i;

	if (format == 0)
		return (-1);
	va_start(args, format);
	char_count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			handle_specifier(format[i], args, &char_count);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			char_count++;
		}
		i++;
	}
	va_end(args);
	return (char_count);
}
