/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:28 by marianfurni       #+#    #+#             */
/*   Updated: 2023/09/15 13:20:57 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d < s)
	{
		while (len--)
		{
			*d++ = *s++;
		}
	}
	else if (d > s)
	{
		d += len;
		s += len;
		while (len--)
		{
			*(--d) = *(--s);
		}
	}
	return (dst);
}
/*#include <stdio.h>
#include <string.h>
#include "libft.h"

int main() {
    char src[20] = "Hello, World!";
    char dest1[20];
    char dest2[20];

    // Using ft_memmove
    ft_memmove(dest1, src, 5);
    printf("Result of ft_memmove: %s\n", dest1);

    // Using memmove from the C standard library
    memmove(dest2, src, 5);
    printf("Result of memmove: %s\n", dest2);

    return 0;
}
*/
