/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_graphics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:39:49 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 22:17:08 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	initialize_graphics(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (free(data), MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "fract-ol");
	if (data->win_ptr == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (free(data), MLX_ERROR);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->img.mlx_img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (free(data), MLX_ERROR);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
	return (0);
}

void	free_image(t_data *data)
{
	if (data->img.mlx_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
}

int	calculate_smaller_dimension(t_data *data)
{
	int	smaller_dimension;

	if (WIN_HEIGHT <= 0 || WIN_WIDTH <= 0)
	{
		free_image(data);
		ft_printf("Invalid window size. Please use nbr > 0.\n");
		exit(EXIT_FAILURE);
	}
	if (WIN_HEIGHT < WIN_WIDTH)
		smaller_dimension = WIN_HEIGHT;
	else
		smaller_dimension = WIN_WIDTH;
	return (smaller_dimension);
}

void	setup_fractal_defaults(t_data *data)
{
	data->move_x = 0;
	data->move_y = 0;
	data->iter = 0;
	data->color = 0;
	data->color_man = 0x0000FF;
	data->x_min = -2;
	data->x_max = 2;
	data->y_min = -2;
	data->y_max = 2;
	data->small_side = calculate_smaller_dimension(data);
	data->zoom = 1;
	data->mouse_x = 0;
	data->mouse_y = 0;
	data->zoom_factor = 0.9;
	ft_draw_fractals(data);
}
