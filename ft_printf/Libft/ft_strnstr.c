/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:25:40 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include <bsd/string.h>
#include "libft.h"

int main()
{
    const char *big = "This is a simple example.";
    const char *little = "simple";

    char *result1 = strnstr(big, little, 110);
    char *result2 = ft_strnstr(big, little, 110);

    printf("Result strnstr: %s\n", result1 ? result1 : "NULL");
    printf("Result ft_strnstr: %s\n", result2 ? result2 : "NULL");

    return 0;
}*/
