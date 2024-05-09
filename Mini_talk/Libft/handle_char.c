/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:37:12 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/04 16:07:05 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_char(va_list args, int *char_count)
{
	char	c;

	c = va_arg(args, int);
	ft_putchar_fd(c, 1);
	(*char_count)++;
}
