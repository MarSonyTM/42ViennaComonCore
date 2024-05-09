/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:05:01 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/18 17:44:14 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	append_node(t_list **new_lst, t_list **tail, t_list *new_node)
{
	if (*tail)
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
	else
	{
		*new_lst = new_node;
		*tail = new_node;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*tail;

	new_lst = NULL;
	new_node = NULL;
	tail = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		append_node(&new_lst, &tail, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
