/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:56:50 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/08 15:23:21 by mafurnic         ###   ########.fr       */
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
