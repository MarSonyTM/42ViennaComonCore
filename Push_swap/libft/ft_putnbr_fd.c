/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:09:24 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/17 13:07:26 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[13];
	int		is_neg;
	int		length;

	is_neg = (n < 0);
	ft_bzero(str, 13);
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (is_neg)
		str[length++] = '-';
	else if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}
/*#include "libft.h"
#include <stdio.h>

int main(void)
{
    // Testing with standard output
    ft_putnbr_fd(12345, 1);
    write(1, "\n", 1);

    ft_putnbr_fd(-12345, 1);
    write(1, "\n", 1); 

    // Testing with 0
    ft_putnbr_fd(0, 1);
    write(1, "\n", 1); 

  
    ft_putnbr_fd(-2147483648, 1);
    write(1, "\n", 1);

    return 0;
}*/
