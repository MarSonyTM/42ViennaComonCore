/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:25:25 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
/*#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int main()
{
    char src[] = "Hello, World!";
    char dst1[20];
    char dst2[20];
    size_t result1, result2;

    // Test 1: Normal case
    result1 = ft_strlcpy(dst1, src, sizeof(dst1));
    result2 = strlcpy(dst2, src, sizeof(dst2));
    printf("Test 1:\n");
    printf("ft_strlcpy: %zu, %s\n", result1, dst1);
    printf("strlcpy  : %zu, %s\n", result2, dst2);
 
   // Test 2: Smaller destination buffer
    result1 = ft_strlcpy(dst1, src, 5);
    result2 = strlcpy(dst2, src, 5);
    printf("\nTest 2:\n");
    printf("ft_strlcpy: %zu, %s\n", result1, dst1);
    printf("strlcpy  : %zu, %s\n", result2, dst2);
    
    // Test 3: Destination buffer of size 0
    result1 = ft_strlcpy(dst1, src, 0);
    result2 = strlcpy(dst2, src, 0);
    printf("\nTest 3:\n");
    printf("ft_strlcpy: %zu, %s\n", result1, dst1);
    printf("strlcpy  : %zu, %s\n", result2, dst2);
    
    // Test 4: Empty source string
    char empty[] = "";
    result1 = ft_strlcpy(dst1, empty, sizeof(dst1));
    result2 = strlcpy(dst2, empty, sizeof(dst2));
    printf("\nTest 4:\n");
    printf("ft_strlcpy: %zu, %s\n", result1, dst1);
    printf("strlcpy  : %zu, %s\n", result2, dst2);

    return (0);
}*/
// cc with -lbsd
