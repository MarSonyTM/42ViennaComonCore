/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:02:00 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:02 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_stacks(t_list **stack_a, t_list **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
}

int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;

	if (ac < 2)
		return (-1);
	ft_checkargs(ac, av);
	stack_a = (t_list **)malloc(sizeof(t_list *));
	if (stack_a == NULL)
		return (1);
	stack_b = (t_list **)malloc(sizeof(t_list *));
	if (stack_b == NULL)
		return (free(stack_a), 1);
	*stack_a = NULL;
	*stack_b = NULL;
	if (initializestack(stack_a, ac, av) == -1)
		return (free_stacks(stack_a, stack_b), 1);
	if (is_sorted(stack_a))
	{
		free_stacks(stack_a, stack_b);
		return (0);
	}
	sort_stack(stack_a, stack_b);
	free_stacks(stack_a, stack_b);
	return (0);
}
