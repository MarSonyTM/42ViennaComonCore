/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:46:10 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 11:36:11 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

double	calculate_smooth_color(t_data *data)
{
	double	zn_abs;
	double	nu;

	zn_abs = sqrt(data->coord.z.real_sq + data->coord.z.imaginary_sq);
	nu = log(log(zn_abs) / log(2)) / log(2);
	return (data->iter + 1 - nu);
}

int	color_mandelbrot(t_data *data)
{
	double	smoothed_iter;

	smoothed_iter = calculate_smooth_color(data);
	data->color = (int)(smoothed_iter * (data->color_man * 5) / MAX_ITER) % 256;
	return (data->color);
}

int	color_julia(t_data *data)
{
	double	smoothed_iter;
	int		iter_index;
	int		red;
	int		green;
	int		blue;

	smoothed_iter = calculate_smooth_color(data);
	iter_index = (int)(smoothed_iter * 256 / MAX_ITER_JUL) % 256;
	red = (iter_index * 5) % 256;
	green = (iter_index * 7) % 256;
	blue = (iter_index * 11) % 256;
	data->color = (red << 16) | (green << 8) | blue;
	return (data->color);
}
