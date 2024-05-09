/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:21:55 by mafurnic          #+#    #+#             */
/*   Updated: 2023/12/06 15:22:32 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *snew)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = snew;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = snew;
}
/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    t_list *head = NULL;
    t_list *new_node;

    // node to the front of the list
    new_node = ft_lstnew("Hello");
    ft_lstadd_front(&head, new_node);

    //  node to the end of the list
    new_node = ft_lstnew("World");
    ft_lstadd_back(&head, new_node);

    // Printinting the content of the last node
    printf("Last node content: %s\n", (char*)ft_lstlast(head)->content);

    return (0);
}
*/