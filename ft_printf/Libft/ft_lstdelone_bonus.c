/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:35:36 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 16:41:34 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
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
    t_list *node;

    node = ft_lstnew(strdup("Hello, World!")); 

    printf("Before deletion: %s\n", (char*)node->content);

    ft_lstdelone(node, simple_del);

    // It's not safe to access 'node' after it has been freed.
    // Just for demonstration, we show that it's no longer valid.
    //printf("After deletion: %s\n", (char*)node->content);

    return 0;
}
*/