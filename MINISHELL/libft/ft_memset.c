/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:10:39 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:57 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}
/*#include "libft.h"
#include <stdio.h>
#include <string.h>

int main()
{
   
    char str1[] = "Hello, World!";
    char str2[] = "Hello, World!";
    int value1 = 'X';
    size_t len1 = 5;

    ft_memset(str1, value1, len1);
    memset(str2, value1, len1);

    printf("Test case 1 ft_memset - Modified str1: %s\n", str1);
    printf("Test case 1    memset- Modified str2: %s\n", str2);

    char str3[] = "Hello, World!";
    int value2 = 'Y';
    size_t len2 = 10;

    ft_memset(str3, value2, len2);
    memset(str2, value2, len2);

    printf("Test case 2 ft_memset - Modified str3: %s\n", str3);
    printf("Test case 2    memset- Modified str2: %s\n", str2);

    return 0;
}*/
