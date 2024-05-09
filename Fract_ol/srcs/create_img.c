/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:46:45 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/12 18:20:36 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(int *)pixel = color;
}

void	ft_draw_fractals(t_data *data)
{
	if (data->launch == 1)
		fractal_mandelbrot(data);
	else if (data->launch == 2)
		fractal_julia(data);
	else if (data->launch == 3)
		fractal_burningship(data);
}
