/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:45:02 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:14 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	char s1[] = "Green";
	char s2[] = "GreenWorld";

	int result1 = strncmp(s1,s2,-5);
	int result2 = ft_strncmp(s1,s2,-5);

	printf("Result strncmp = %d\n",result1);
	printf("result ft_strncmp = %d\n",result2);
}*/
