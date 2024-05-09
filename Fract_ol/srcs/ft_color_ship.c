/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_ship.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:25:48 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 11:36:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	calculate_red(int iter_index)
{
	if (iter_index < 85)
		return (iter_index * 3);
	return (255);
}

int	calculate_green(int iter_index)
{
	int	green;

	if (iter_index < 85)
	{
		green = 0;
	}
	else if (iter_index < 170)
	{
		green = (iter_index - 85) * 3;
		if (green > 255)
			green = 255;
	}
	else
		green = 255;
	return (green);
}

int	color_burning_ship(t_data *data)
{
	double	smoothed_iter;
	int		iter_index;
	int		red;
	int		green;

	smoothed_iter = calculate_smooth_color(data);
	iter_index = (int)(smoothed_iter * 256 / MAX_ITER) % 256;
	red = calculate_red(iter_index);
	green = calculate_green(iter_index);
	data->color = (red << 16) | (green << 8);
	return (data->color);
}
