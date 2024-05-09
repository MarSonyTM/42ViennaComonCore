/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:38:32 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/13 22:16:09 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "./Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdbool.h>

// Window dimensions and error codes
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define MLX_ERROR -1

// Iteration limits for fractals
# define MAX_ITER 200
# define MAX_ITER_JUL 300

// Event handling constants
# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define DESTROY_NOTIFY 17

// Structure for image data
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// Structure for complex numbers
typedef struct s_complex
{
	double	real;
	double	imaginary;
	double	real_sq;
	double	imaginary_sq;
}	t_complex;

// Structure for fractal coordinates
typedef struct s_coord
{
	int			pixel_x;
	int			pixel_y;
	t_complex	z;
	t_complex	c;
}	t_coord;

// Main data structure for the fractal program
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	move_x;
	double	move_y;
	int		launch;
	t_coord	coord;
	int		color;
	int		color_man;
	int		iter;
	double	x_min;
	double	x_max;
	int		small_side;
	double	y_min;
	double	y_max;
	double	zoom;
	double	mouse_x;
	double	mouse_y;
	double	zoom_factor;
}	t_data;

// Function prototypes
int		initialize_graphics(t_data *data);
int		ft_key_handler(int keysym, t_data *data);
int		ft_mouse_handler(int keysym, int px, int py, t_data *data);
int		ft_close_fractal(t_data *data);
int		color_mandelbrot(t_data *data);
int		color_julia(t_data *data);
int		color_burning_ship(t_data *data);

void	display_invalid_args(void);
void	setup_fractal_defaults(t_data *data);
void	ft_draw_fractals(t_data *data);
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	fractal_mandelbrot(t_data *data);
void	ft_mandelbrot_reset(t_data *data);
void	ft_julia_reset(t_data *data);
void	fractal_julia(t_data *data);
void	ft_zoom_in(t_data *data, int px, int py);
void	ft_zoom_out(t_data *data, int px, int py);
void	fractal_burningship(t_data *data);
void	free_image(t_data *data);
void	ft_common_part(t_data *data);
void	ft_handle_error(char *msg);
double	calculate_smooth_color(t_data *data);

bool	check_args_and_initialize(int argc, char **argv, t_data *data);
bool	set_julia_params(t_data *data, char **argv);
bool	is_valid_float(const char *str);

#endif
