/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:02:14 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	sort_with_min_at_top(t_list **stack_a, int next_min)
{
	if ((*stack_a)->next->index != next_min)
	{
		ra(stack_a);
		sa(stack_a);
		rra(stack_a);
	}
}

static void	sort_with_next_min_at_top(t_list **stack_a, int min)
{
	if ((*stack_a)->next->index == min)
		sa(stack_a);
	else
		rra(stack_a);
}

static void	sort_remaining_case(t_list **stack_a, int min)
{
	if ((*stack_a)->next->index == min)
		ra(stack_a);
	else
	{
		sa(stack_a);
		rra(stack_a);
	}
}

void	sort3(t_list **stack_a)
{
	t_list		*head;
	int			min;
	int			next_min;

	head = *stack_a;
	min = get_min(stack_a, -1);
	next_min = get_min(stack_a, min);
	if (is_sorted(stack_a))
		return ;
	if (head->index == min)
		sort_with_min_at_top(stack_a, next_min);
	else if (head->index == next_min)
		sort_with_next_min_at_top(stack_a, min);
	else
		sort_remaining_case(stack_a, min);
}
