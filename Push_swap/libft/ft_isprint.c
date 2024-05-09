/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:15:39 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>
*/
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
int	main()
{
	 char test_char = 'A';

	int	original_result = isprint(test_char);
	int	ft_result = ft_isprint(test_char);
	
	printf("Character: %c (ASCII: %d)\n", test_char, (int)test_char);
    printf("Original isprint: %d\n", original_result);
    printf("Custom ft_isprint: %d\n", ft_result);
}*/
