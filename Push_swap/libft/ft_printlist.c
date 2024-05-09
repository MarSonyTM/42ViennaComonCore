/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:00:15 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/17 13:11:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printlist(t_list	*head)
{
	t_list	*temp;

	temp = head;
	while (temp != NULL)
	{
		ft_putnbr_fd(temp->content, 1);
		ft_putstr_fd("", 1);
		temp = temp->next;
	}
}
