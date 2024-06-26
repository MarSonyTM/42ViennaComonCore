/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:47:44 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/04 16:07:23 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
