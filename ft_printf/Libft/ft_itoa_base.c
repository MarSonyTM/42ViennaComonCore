/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:58:08 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/21 15:40:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen_base(int n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

static char	*initialize_and_malloc(int *is_negative, int *len)
{
	if (*is_negative == 1)
		*len = *len + 1;
	return ((char *)malloc(sizeof(char) * (*len + 1)));
}

static void	fill_res_str(char *res, unsigned int un, int base, int len)
{
	const char	*digits;

	digits = "0123456789abcdef";
	while (len--)
	{
		res[len] = digits[un % base];
		un /= base;
	}
}

static unsigned int	handle_negatives(int *n, int base, int *is_negative)
{
	unsigned int	un;

	if (*n < 0)
	{
		if (base == 10)
		{
			*is_negative = 1;
		}
		else
		{
			*is_negative = 0;
		}
		un = (unsigned int)(-(*n));
	}
	else
	{
		un = (unsigned int)(*n);
		*is_negative = 0;
	}
	return (un);
}

char	*ft_itoa_base(int n, int base)
{
	int				is_negative;
	int				len;
	char			*res;
	unsigned int	un;

	is_negative = 0;
	if (base < 2 || base > 16)
		return (NULL);
	un = handle_negatives(&n, base, &is_negative);
	len = ft_numlen_base(un, base);
	res = initialize_and_malloc(&is_negative, &len);
	if (!res)
		return (NULL);
	fill_res_str(res, un, base, len);
	if (is_negative)
		res[0] = '-';
	return (res);
}
