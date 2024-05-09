/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:03:32 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/04 16:07:09 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_hex_lower(va_list args, int *char_count)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	(*char_count) += ft_putnbr_base_fd(number, 16, 1, 0);
}
