/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:16:59 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	char str[] = "theanswerisfortytw";
	int character = 'y';

	char *result1 = ft_memchr(str, character, strlen(str));
	printf("ft_memchr = %s\n", result1);
	
	char *result2 = memchr(str, character , strlen(str));
	printf("memchr = %s\n", result2);

	return(0);
}*/
