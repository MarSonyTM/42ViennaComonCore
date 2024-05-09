/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:34:53 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;

	last_occurrence = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			last_occurrence = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (last_occurrence);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	const char *str = "Los Angeles";
	int character = '\0';

	const char *std_result = strrchr(str, character);

	char *ft_result = ft_strrchr(str, character);

	printf("Standard strrchr result: %s\n", std_result ? std_result : "NULL");
    printf("Custom ft_strrchr result: %s\n", ft_result ? ft_result : "NULL");

	return (0);
}*/	
