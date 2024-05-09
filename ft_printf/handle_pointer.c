/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:47:44 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/26 10:04:18 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_pointer(va_list args, int *char_count)
{
	unsigned long long	address;

	address = (unsigned long long)va_arg(args, void *);
	if (address == 0)
	{
		ft_putstr_fd("(nil)", 1);
		(*char_count) += 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		(*char_count) += 2;
		(*char_count) += ft_putnbr_base_fd(address, 16, 1, 0);
	}
}
