/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:40:31 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/12 18:24:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	ft_julia_reset(t_data *data)
{
	data->iter = 0;
	data->coord.z.real = data->x_min + (data->coord.pixel_x + data->move_x)
		* (data->x_max - data->x_min) / data->small_side;
	data->coord.z.imaginary = data->y_max - (data->coord.pixel_y + data->move_y)
		* (data->y_max - data->y_min) / data->small_side;
	data->coord.z.real_sq = data->coord.z.real * data->coord.z.real;
	data->coord.z.imaginary_sq = data->coord.z.imaginary
		* data->coord.z.imaginary;
}

void	fractal_julia(t_data *data)
{
	data->coord.pixel_y = 0;
	while (data->coord.pixel_y <= WIN_HEIGHT)
	{
		data->coord.pixel_x = 0;
		while (data->coord.pixel_x <= WIN_WIDTH)
		{
			ft_julia_reset(data);
			ft_common_part(data);
			ft_pixel_put(data, data->coord.pixel_x,
				data->coord.pixel_y, color_julia(data));
			data->coord.pixel_x++;
		}
		data->coord.pixel_y++;
	}
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
}
