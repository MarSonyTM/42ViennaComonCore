/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_burningship.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:48:39 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 11:35:57 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

static void	ft_burning_ship(t_data *data)
{
	while (data->coord.z.real_sq + data->coord.z.imaginary_sq < 4
		&& data->iter < MAX_ITER)
	{
		data->coord.z.imaginary = fabsl(2 * data->coord.z.real
				* data->coord.z.imaginary - data->coord.c.imaginary);
		data->coord.z.real = fabsl(data->coord.z.real_sq
				- data->coord.z.imaginary_sq + data->coord.c.real);
		data->coord.z.real_sq = data->coord.z.real * data->coord.z.real;
		data->coord.z.imaginary_sq
			= data->coord.z.imaginary * data->coord.z.imaginary;
		data->iter++;
	}
}

void	fractal_burningship(t_data *data)
{
	data->coord.pixel_y = 0;
	while (data->coord.pixel_y <= WIN_HEIGHT)
	{
		data->coord.pixel_x = 0;
		while (data->coord.pixel_x <= WIN_WIDTH)
		{
			ft_mandelbrot_reset(data);
			ft_burning_ship(data);
			ft_pixel_put(data, data->coord.pixel_x,
				data->coord.pixel_y, color_burning_ship(data));
			data->coord.pixel_x++;
		}
		data->coord.pixel_y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
}
