/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:37:12 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/08 15:23:02 by mafurnic         ###   ########.fr       */
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
