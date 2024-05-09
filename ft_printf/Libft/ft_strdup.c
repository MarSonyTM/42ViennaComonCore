/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:30:54 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:34:20 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*d;

	i = 0;
	len = 0;
	len = ft_strlen(s);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	while (i <= len)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	const char *src = "!@#$%^&*()_+{}[];:'<>,.?/\\";

	char *result = ft_strdup(src);
	printf("ft_strdup : %s\n", result);

	char *result1 = strdup(src);
	printf("strdup : %s\n", result1);

	return (0);
}*/
