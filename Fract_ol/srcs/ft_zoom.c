/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:42:52 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/12 18:34:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	ft_zoom_in(t_data *data, int mouse_x_position, int mouse_y_position)
{
	data->mouse_x = data->x_min + (mouse_x_position + data->move_x)
		* (data->x_max - data->x_min) / data->small_side;
	data->mouse_y = data->y_max - (mouse_y_position + data->move_y)
		* (data->y_max - data->y_min) / data->small_side;
	data->x_min = data->mouse_x - (data->mouse_x - data->x_min)
		* data->zoom_factor;
	data->y_min = data->mouse_y - (data->mouse_y - data->y_min)
		* data->zoom_factor;
	data->x_max = data->mouse_x - (data->mouse_x - data->x_max)
		* data->zoom_factor;
	data->y_max = data->mouse_y - (data->mouse_y - data->y_max)
		* data->zoom_factor;
	data->zoom *= data->zoom_factor;
}

void	ft_zoom_out(t_data *data, int mouse_x_position, int mouse_y_position)
{
	data->mouse_x = data->x_min + (mouse_x_position + data->move_x)
		* (data->x_max - data->x_min) / data->small_side;
	data->mouse_y = data->y_max - (mouse_y_position + data->move_y)
		* (data->y_max - data->y_min) / data->small_side;
	data->x_min = data->mouse_x - (data->mouse_x - data->x_min)
		/ data->zoom_factor;
	data->y_min = data->mouse_y - (data->mouse_y - data->y_min)
		/ data->zoom_factor;
	data->x_max = data->mouse_x - (data->mouse_x - data->x_max)
		/ data->zoom_factor;
	data->y_max = data->mouse_y
		- (data->mouse_y - data->y_max) / data->zoom_factor;
	data->zoom /= data->zoom_factor;
}
