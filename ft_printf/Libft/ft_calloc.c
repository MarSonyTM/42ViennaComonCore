/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:02:42 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:49 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (count && SIZE_MAX / count < size)
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, total_size);
	}
	return (ptr);
}
/*
int main()
{
    size_t num_elements = 5;
    size_t element_size = sizeof(int);

    // Using ft_calloc
    int *ft_ptr = ft_calloc(num_elements, element_size);
    if (ft_ptr != NULL)
    {
        printf("ft_calloc: Memory allocated successfully\n");
        free(ft_ptr);
    }
    else
    {
        printf("ft_calloc: Memory allocation failed\n");
    }

    // Using standard calloc
    int *calloc_ptr = calloc(num_elements, element_size);
    if (calloc_ptr != NULL)
    {
        printf("calloc: Memory allocated successfully\n");
        free(calloc_ptr);
    }
    else
    {
        printf("calloc: Memory allocation failed\n");
    }

    return 0;
}*/
