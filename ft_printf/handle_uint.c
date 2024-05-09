/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:59:47 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/25 14:44:02 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_uint(va_list args, int *char_count)
{
	unsigned int	number;
	char			*num_str;

	number = va_arg(args, unsigned int);
	num_str = ft_uitoa(number);
	if (num_str)
	{
		ft_putstr_fd(num_str, 1);
		(*char_count) += ft_strlen(num_str);
		free(num_str);
	}
}
