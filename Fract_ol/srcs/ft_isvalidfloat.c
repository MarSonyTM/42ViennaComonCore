/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalidfloat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:26:05 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 21:36:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

static int	skip_sign(const char *str)
{
	if (*str == '+' || *str == '-')
	{
		return (1);
	}
	return (0);
}

static int	skip_digits(const char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
	{
		i++;
	}
	return (i);
}

bool	is_valid_float(const char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	i += skip_sign(str + i);
	i += skip_digits(str + i);
	if (str[i] == '.')
	{
		i++;
		dot_count++;
	}
	i += skip_digits(str + i);
	if (str[i] == 'e' || str[i] == 'E')
	{
		i++;
		i += skip_sign(str + i);
		i += skip_digits(str + i);
	}
	return (str[i] == '\0' && dot_count <= 1);
}
