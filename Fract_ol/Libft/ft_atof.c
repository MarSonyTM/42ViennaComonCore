/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:23 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/12 18:41:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nptr)
{
	double	res;
	double	resf;
	char	*ptr;
	int		len;
	int		sign;

	sign = 1;
	ptr = (char *)nptr;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	res = (double)ft_atoi(ptr);
	while (*ptr && *ptr != '.')
		ptr++;
	if (*ptr == '.')
		ptr++;
	resf = (double)ft_atoi(ptr);
	len = ft_strlen(ptr);
	while (len--)
		resf /= 10;
	return ((res + resf) * sign);
}
