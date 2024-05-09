/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:19:18 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:03 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include "libft.h"
#include <stdio.h> 


void capitalize_even(unsigned int i, char *c) {
    if (i % 2 == 0) {
        *c = ft_toupper(*c);
    }
}

int main() {
    char test1[] = "ToUpper";
    char test2[] = "even";
    char test3[] = "iNdeX";

    printf("Before: %s\n", test1);
    ft_striteri(test1, capitalize_even);
    printf("After: %s\n\n", test1);

    printf("Before: %s\n", test2);
    ft_striteri(test2, capitalize_even);
    printf("After: %s\n\n", test2);

    printf("Before: %s\n", test3);
    ft_striteri(test3, capitalize_even);
    printf("After: %s\n\n", test3);

    return 0;
}
*/
