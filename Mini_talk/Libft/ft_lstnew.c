/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:48:42 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 15:05:07 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*#include "libft.h"
#include <stdio.h>

int main()
{
    char *content = "Test content";
    t_list *new_node = ft_lstnew(content);

    if (new_node->content == content && new_node->next == NULL)
        printf("ft_lstnew works correctly!\n");
    else
        printf("ft_lstnew does not work correctly.\n");

    // Free the allocated memory
    free(new_node);

    return 0;
}
*/
