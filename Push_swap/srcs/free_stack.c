/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:01:29 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:01:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_stack(t_list **stack)
{
	t_list	*head;
	t_list	*tmp;

	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack);
}

void	ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
}

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(0);
}

void	ft_error_args(char *message, char **args)
{
	if (args)
		ft_free_split(args);
	ft_putendl_fd(message, 2);
	exit (1);
}
