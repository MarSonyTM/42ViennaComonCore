/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_upper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:05:53 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/25 14:41:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_hex_upper(va_list args, int *char_count)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	(*char_count) += ft_putnbr_base_fd(number, 16, 1, 1);
}
