/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:01:19 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 16:28:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>

int main(void)
{
    t_list *head = NULL;  // Starting with an empty list
    t_list *new_node;

    // Check the size of an empty list
    printf("Size of list: %d\n", ft_lstsize(head));

    // Add a node to the list
    new_node = ft_lstnew("Hello");
    ft_lstadd_front(&head, new_node);
    printf("Size of list: %d\n", ft_lstsize(head));  // Expected: 1

    // Add another node to the list
    new_node = ft_lstnew("World");
    ft_lstadd_front(&head, new_node);
    printf("Size of list: %d\n", ft_lstsize(head));  // Expected: 2

    return (0);
}
*/