/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:02:23 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:48:06 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	check_alpha(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		if (ft_isalpha(str[count]))
		{
			ft_error("Error");
			return ;
		}
		count++;
	}
}

int	ft_only_space(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
