/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:02:49 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (*nptr == '+' || *nptr == '-')
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}
/*
int main()
{
    char *s1 = "12345";
    char *s2 = "+54321";
    char *s3 = "-6789";
    char *s4 = "  42  ";
    char *s5 = "abc123";
    char *s6 = "   -42";
    
    printf("ft_atoi(\"%s\") = %d\n", s1, ft_atoi(s1));
    printf("atoi(\"%s\") = %d\n", s1, atoi(s1));

    printf("ft_atoi(\"%s\") = %d\n", s2, ft_atoi(s2));
    printf("atoi(\"%s\") = %d\n", s2, atoi(s2));

    printf("ft_atoi(\"%s\") = %d\n", s3, ft_atoi(s3));
    printf("atoi(\"%s\") = %d\n", s3, atoi(s3));

    printf("ft_atoi(\"%s\") = %d\n", s4, ft_atoi(s4));
    printf("atoi(\"%s\") = %d\n", s4, atoi(s4));

    printf("ft_atoi(\"%s\") = %d\n", s5, ft_atoi(s5));
    printf("atoi(\"%s\") = %d\n", s5, atoi(s5));

    printf("ft_atoi(\"%s\") = %d\n", s6, ft_atoi(s6));
    printf("atoi(\"%s\") = %d\n", s6, atoi(s6));

    return (0);
*/
