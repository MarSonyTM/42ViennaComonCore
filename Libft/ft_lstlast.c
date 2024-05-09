/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:12:03 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 16:16:19 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    t_list *head = NULL;
    t_list *new_node;
    t_list *last_node;

    // Add a node to the list
    new_node = ft_lstnew("Hello");
    ft_lstadd_front(&head, new_node);

    // Add another node to the list
    new_node = ft_lstnew("World");
    ft_lstadd_front(&head, new_node);

    // Fetch the last node
    last_node = ft_lstlast(head);
    if (last_node)
        printf("Last node content: %s\n", (char*)last_node->content);
    else
        printf("List is empty.\n");

    return (0);
}
*/