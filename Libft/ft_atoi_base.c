/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:02:35 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/21 12:53:13 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isblank(char c)
{
	int	result;

	result = 0;
	if (c == ' ' || c == '\t')
		result = 1;
	return (result);
}

int	ft_isvalid(char c, int base)
{
	const char	*digits;
	const char	*digits_upper;
	int			i;
	int			result;

	i = 0;
	result = 0;
	digits = "0123456789abcdef";
	digits_upper = "0123456789ABCDEF";
	while (i < base)
	{
		if (c == digits[i] || c == digits_upper[i])
		{
			result = 1;
			break ;
		}
		i++;
	}
	return (result);
}

int	ft_value_of(char c)
{
	int	result;

	result = 0;
	if (c >= '0' && c <= '9')
		result = c - '0';
	else if (c >= 'a' && c <= 'f')
		result = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		result = c - 'A' + 10;
	return (result);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;

	if (base < 2 || base > 16)
		return (0);
	result = 0;
	sign = 1;
	while (ft_isblank(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isvalid(*str, base))
	{
		result = (result * base + ft_value_of(*str));
		str++;
	}
	return (result * sign);
}
/*
#include <stdio.h>

int main()
{
    printf("ft_atoi_base(\"42\", 10) = %d\n", ft_atoi_base("42", 10));
    printf("ft_atoi_base(\"-42\", 10) = %d\n", ft_atoi_base("-42", 10));
    printf("ft_atoi_base(\"101010\", 2) = %d\n", ft_atoi_base("101010", 2));
    printf("ft_atoi_base(\"2a\", 16) = %d\n", ft_atoi_base("2a", 16));
    printf("ft_atoi_base(\"ff\", 16) = %d\n", ft_atoi_base("ff", 16));

    return 0;
}
*/
