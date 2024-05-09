/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:49:36 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:55 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	char p1[] = "GYM";
	char p2[] = "GAP";

	int result1 = ft_memcmp(p1, p2, 2);
	printf("ft_memcmp = %d\n", result1);

	int result2 = memcmp(p1, p2, 2);
	printf("memcmp = %d\n", result2);

	return (0);
}*/
