/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:26:29 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:48 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = '\0';
}
/*
int	main()
{
	char str1[] = "stay on track!";
	char str2[] = "stay on track!";
	size_t n = 1;

	printf("Original str1: %s\n",str1);
	printf("Original str2: %s\n",str2);

	bzero(str1,n);
	ft_bzero(str2,n);

	printf("After bzero str1: %s\n",str1);
	printf("After Bzero  str2: %s\n",str2);

	int arr[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: ");
    for (size_t i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

   
    bzero(arr, sizeof(arr));

    printf("After bzero: ");
    for (size_t i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

   
    int reset_arr[] = {1, 2, 3, 4, 5};

  
    ft_bzero(reset_arr, sizeof(reset_arr));

    printf("After ft_bzero: ");
    for (size_t i = 0; i < count; i++) {
        printf("%d ", reset_arr[i]);
    }
    printf("\n");

    return (0);
}*/
