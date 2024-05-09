/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:11:09 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 11:48:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*extract_word(const char **s, char c)
{
	int			len;
	const char	*start;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	return (ft_substr(start, 0, len));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = extract_word(&s, c);
		if (!result[i])
		{
			while (i-- > 0)
				free (result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
/*int main()
{
    char **words;
    char *str = "Hello  world!   Let's test ft_split.";

    words = ft_split(str, ' ');

    for (int i = 0; words[i]; i++)
    {
        printf("Word[%d]: %s\n", i, words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}*/
