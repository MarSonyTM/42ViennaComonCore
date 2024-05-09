/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:24:11 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 15:37:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*#include <stdio.h>

int main()
{
    char *content1 = "First content";
    char *content2 = "Second content";
    t_list *first_node = ft_lstnew(content1);
    t_list *second_node = ft_lstnew(content2);

    ft_lstadd_front(&first_node, second_node);

    if (first_node == second_node && first_node->next->content == content1)
        printf("ft_lstadd_front works correctly!\n");
    else
        printf("ft_lstadd_front does not work correctly.\n");

    // Free the allocated memory
    free(first_node->next);
    free(first_node);

    return 0;
}*/