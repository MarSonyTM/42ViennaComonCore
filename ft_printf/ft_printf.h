/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:56:30 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/27 16:12:09 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "Libft/libft.h"

int			ft_printf(const char *str, ...);
void		handle_specifier(char specifier, va_list args, int *char_count);
void		handle_char(va_list args, int *char_count);
void		handle_string(va_list args, int *char_count);
void		handle_pointer(va_list args, int *char_count);
void		handle_int(va_list args, int *char_count);
void		handle_uint(va_list args, int *char_count);
void		handle_hex_lower(va_list args, int *char_count);
void		handle_hex_upper(va_list args, int *char_count);
void		handle_percent(int *char_count);

#endif