/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:56:41 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/28 16:41:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		char_count;
	int		i;

	if (format == 0)
		return (-1);
	va_start(args, format);
	char_count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			handle_specifier(format[i], args, &char_count);
		}
		else
		{
			write(1, &format[i], 1);
			char_count++;
		}
		i++;
	}
	va_end(args);
	return (char_count);
}
/*
#include <stdio.h>

int main(void)
{
    char character = 'A';
    char *string = "Hello, World!";
    void *pointer = &character;
    int integer = -42;
    unsigned int u_integer = 42;
    int hex = 255;
    
    // Testing %c specifier
    printf("Standard printf character: %c\n", character);
    ft_printf("Your ft_printf character: %c\n", character);
    
    // Testing %s specifier
    printf("Standard printf string: %s\n", string);
    ft_printf("Your ft_printf string: %s\n", string);
    
    // Testing %p specifier
    printf("Standard printf pointer: %p\n", pointer);
     ft_printf("Your ft_printf pointer: %p\n", pointer);
    
    // Testing %d and %i specifier
    printf("Standard printf integer: %d %i\n", integer, integer);
    ft_printf("Your ft_printf integer: %d %i\n", integer, integer);
    
    // Testing %u specifier
    printf("Standard printf unsigned integer: %u\n", u_integer);
    ft_printf("Your ft_printf unsigned integer: %u\n", u_integer);
    
    // Testing %x specifier
    printf("Standard printf hexadecimal (lowercase): %x\n", hex);
    ft_printf("Your ft_printf hexadecimal (lowercase): %x\n", hex);
    
    // Testing %X specifier
    printf("Standard printf hexadecimal (uppercase): %X\n", hex);
    ft_printf("Your ft_printf hexadecimal (uppercase): %X\n", hex);
    
    // Testing %% specifier
    printf("Standart printfpercent sign: %%\n");
	ft_printf("Your ft_printf percent sign: %%\n");
    return 0;
}
*/
