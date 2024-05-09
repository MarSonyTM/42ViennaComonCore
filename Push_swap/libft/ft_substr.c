/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 08:26:24 by marianfurni       #+#    #+#             */
/*   Updated: 2023/09/15 13:21:18 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include <stdlib.h>
/*#include <string.h>

unsigned long	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*d;

	i = 0;
	len = 0;
	if (s == NULL)
		return (NULL);
	while (s[len] != '\0')
	{
		len++;
	}
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
    d[i] = '\0';
	return (d);
}
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*#include <stdio.h>

int main(void)
{
    char *input;
    char *result;

    input = "Hello, World!";
    result = ft_substr(input, 7, 5);
    printf("Expected: World   | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 0, 5);
    printf("Expected: Hello   | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 7, 6);
    printf("Expected: World!  | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 50, 5);
    printf("Expected: (empty) | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 7, 50);
    printf("Expected: World!  | Result: %s\n", result);
    free(result);

    result = ft_substr(NULL, 0, 5);
    printf("Expected: (NULL)  | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 5, 0);
    printf("Expected: (empty) | Result: %s\n", result);
    free(result);

    input = "Hello, World!";
    result = ft_substr(input, 13, 5);
    printf("Expected: (empty) | Result: %s\n", result);
    free(result);

}*/
