/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:37:12 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/25 14:41:27 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_char(va_list args, int *char_count)
{
	char	c;

	c = va_arg(args, int);
	ft_putchar_fd(c, 1);
	(*char_count)++;
}
