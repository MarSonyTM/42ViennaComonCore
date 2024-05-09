/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:37:38 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 22:24:58 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
	{
		ft_handle_error("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (!check_args_and_initialize(argc, argv, data))
	{
		display_invalid_args();
		free(data);
		exit(EXIT_FAILURE);
	}
	if (initialize_graphics(data) != 0)
	{
		ft_handle_error("Error initializing graphics");
		exit(EXIT_FAILURE);
	}
	setup_fractal_defaults(data);
	mlx_hook(data->win_ptr, KEY_PRESS, KEY_PRESS_MASK, &ft_key_handler, data);
	mlx_mouse_hook(data->win_ptr, &ft_mouse_handler, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY, 0, &ft_close_fractal, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
