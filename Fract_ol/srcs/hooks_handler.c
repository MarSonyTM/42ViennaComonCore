/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:43:52 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 09:51:07 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	ft_key_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_close_fractal(data);
	else if (keysym == XK_Up)
		data->move_y -= (WIN_HEIGHT / 20.0);
	else if (keysym == XK_Down)
		data->move_y += (WIN_HEIGHT / 20.0);
	else if (keysym == XK_Left)
		data->move_x -= (WIN_HEIGHT / 20.0);
	else if (keysym == XK_Right)
		data->move_x += (WIN_HEIGHT / 20.0);
	else if (keysym == XK_c)
		data->color_man += 256;
	else if (keysym == XK_r)
		setup_fractal_defaults(data);
	ft_draw_fractals(data);
	return (0);
}

int	ft_mouse_handler(int keysym, int px, int py, t_data *data)
{
	if (keysym == 4)
		ft_zoom_in(data, px, py);
	if (keysym == 5)
		ft_zoom_out(data, px, py);
	ft_draw_fractals(data);
	return (0);
}

int	ft_close_fractal(t_data *data)
{
	free_image(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	exit(0);
}
