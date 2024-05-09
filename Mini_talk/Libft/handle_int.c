/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:56:50 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/04 16:07:16 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_int(va_list args, int *char_count)
{
	int		number;
	char	*num_str;

	number = va_arg(args, int);
	num_str = ft_itoa(number);
	if (num_str)
	{
		ft_putstr_fd(num_str, 1);
		(*char_count) += ft_strlen(num_str);
		free(num_str);
	}
}
