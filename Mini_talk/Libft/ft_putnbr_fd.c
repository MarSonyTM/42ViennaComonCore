/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:09:24 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			c;

	if (n < 0)
	{
		c = '-';
		write (fd, &c, 1);
		num = -n;
	}
	else
	{
		num = n;
	}
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
	}
	c = (num % 10) + '0';
	write(fd, &c, 1);
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
