/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:43 by marianfurni       #+#    #+#             */
/*   Updated: 2023/09/15 13:35:36 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	d = (char *)dst;
	s = (const char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*#include "libft.h"
#include <stdio.h>
#include <string.h>

int main() {
    
    char src[] = "Hello, World!";
    char dst1[20];
    char dst2[20];
	
    printf("Result of ft_memcpy: %s\n", dst1);
    printf("Result of memcpy: %s\n", dst2);
   
    return (0);
}*/
