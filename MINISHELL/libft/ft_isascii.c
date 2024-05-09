/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:08:39 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*
int	main()
{
	char c = '+';

	printf("%d\n", isascii(c));
	printf("%d\n",ft_isascii(c));
}*/
