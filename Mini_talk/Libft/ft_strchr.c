/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:02:08 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:01 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	const char *str = "Vienna";
	int character = '\0';

	const char *std_result = strchr(str, character);

	char *ft_result = ft_strchr(str, character);

	printf("Standard strchr result: %s\n", std_result ? std_result : "NULL");
    printf("Custom ft_strchr result: %s\n", ft_result ? ft_result : "NULL");
}*/
