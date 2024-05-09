/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:27:27 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/25 14:27:00 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned long long n, int base, int fd, int uppercase)
{
	const char	*digits_lower;
	const char	*digits_upper;
	const char	*chosen_digits;
	int			char_count;

	char_count = 1;
	digits_lower = "0123456789abcdef";
	digits_upper = "0123456789ABCDEF";
	if (uppercase)
		chosen_digits = digits_upper;
	else
		chosen_digits = digits_lower;
	if (base < 2 || base > 16)
		return (0);
	if (n >= (unsigned long long)base)
		char_count += ft_putnbr_base_fd(n / base, base, fd, uppercase);
	ft_putchar_fd(chosen_digits[n % base], fd);
	return (char_count);
}
