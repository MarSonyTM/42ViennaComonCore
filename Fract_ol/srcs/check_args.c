/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:47:23 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 22:04:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fract_ol.h"

void	display_invalid_args(void)
{
	ft_printf("\n\n\t\t INVALID INPUT\n\n");
	ft_printf("\navailable fractals : Mandelbrot, Julia and Burningship\n\n");
	ft_printf("for Mandelbrot use  ./fractol mandelbrot\n\n");
	ft_printf("for Burningship use ./fractol burningship\n\n");
	ft_printf("for Julia: ");
	ft_printf("./fractol julia x y (x and y are complex numbers \n");
	ft_printf("for best results first arg from 0.275 to 0.300");
	ft_printf(" and second from 0.001 to 0.009\n");
	ft_printf("enjoy the view!\n");
}

void	validate_arg(char *arg, t_data *data)
{
	double	tmp;

	if (!is_valid_float(arg))
	{
		ft_printf("Error: Invalid number format\n");
		free(data);
		exit(EXIT_FAILURE);
	}
	tmp = ft_atof(arg);
	if (tmp < -2.0 || tmp > 2.0)
	{
		ft_printf("Error: Number out of range\n");
		free(data);
		exit(EXIT_FAILURE);
	}
}

bool	set_julia_params(t_data *data, char **argv)
{
	validate_arg(argv[2], data);
	validate_arg(argv[3], data);
	data->coord.c.real = ft_atof(argv[2]);
	data->coord.c.imaginary = ft_atof(argv[3]);
	return (data->coord.c.real > -2 && data->coord.c.real < 2
		&& data->coord.c.imaginary > -2 && data->coord.c.imaginary < 2);
}

bool	check_args_and_initialize(int argc, char **argv, t_data *data)
{
	if (argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
	{
		data->launch = 1;
		return (true);
	}
	else if (argc == 2 && !ft_strcmp(argv[1], "burningship"))
	{
		data->launch = 3;
		return (true);
	}
	else if (argc == 4 && !ft_strcmp(argv[1], "julia")
		&& set_julia_params(data, argv))
	{
		data->launch = 2;
		return (true);
	}
	return (false);
}
