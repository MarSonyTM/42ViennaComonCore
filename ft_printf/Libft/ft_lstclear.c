/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:43:39 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 16:55:43 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*current;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current->next;
		ft_lstdelone(current, del);
		current = tmp;
	}
	*lst = NULL;
}
/*
#include "libft.h"
#include <stdio.h>

void simple_del(void *content)
{
    free(content);
}

int main(void)
{
    t_list *list = NULL;
    t_list *node1 = ft_lstnew(strdup("Node 1"));
    t_list *node2 = ft_lstnew(strdup("Node 2"));
    t_list *node3 = ft_lstnew(strdup("Node 3"));

    ft_lstadd_back(&list, node1);
    ft_lstadd_back(&list, node2);
    ft_lstadd_back(&list, node3);

    printf("Before clearing the list:\n");
    t_list *temp = list;
    while (temp)
    {
        printf("%s\n", (char*)temp->content);
        temp = temp->next;
    }

    ft_lstclear(&list, simple_del);

    printf("\nAfter clearing the list:\n");
    if (list == NULL)
    {
        printf("List is now NULL\n");
    }
    else
    {
        temp = list;
        while (temp)
        {
            printf("%s\n", (char*)temp->content);
            temp = temp->next;
        }
    }

    return 0;
}
*/