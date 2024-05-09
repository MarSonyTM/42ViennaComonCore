/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:44:14 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
int	main()
{
	int d = 'i';

	printf("%d\n", isdigit(d));
	printf("%d\n", ft_isdigit(d));
}*/
