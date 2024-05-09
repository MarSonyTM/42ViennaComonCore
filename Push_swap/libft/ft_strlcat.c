/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:43:21 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:07 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = 0;
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size <= dst_len)
		return (src_len + size);
	i = dst_len;
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < size)
		dst[i] = '\0';
	return (dst_len + src_len);
}
/*
#include <bsd/string.h>

int	main()
{
	char dest[20] = "Hello, ";
	char src[] = "World!";
	unsigned int size = -7;

	unsigned int result = ft_strlcat(dest, src, size);
	printf("%s\n", dest);
	printf("%u\n",result);

	char dest1[20] = "Hello, ";
	char src1[] = "World!";
	unsigned int size1 = -7;

    unsigned int result1 = strlcat(dest1, src1, size1);
    printf("%s\n", dest);
    printf("%u\n",result1);
}*/
// cc ft_strlcat.c -lbsd
