/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:01:36 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:01:39 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static int	add_elements_to_stack(t_list **stack, char **args, int ac)
{
	t_list	*new;
	int		i;

	i = 0;
	while (args[i])
	{
		new = ft_lstnew(ft_atoi(args[i]));
		if (!new)
		{
			if (ac == 2)
				ft_free_split(args);
			return (-1);
		}
		ft_lstadd_back(stack, new);
		i++;
	}
	return (0);
}

int	initializestack(t_list **stack, int ac, char **av)
{
	char	**args;
	int		result;

	if (ac == 2)
	{
		args = ft_split(av[1], ' ');
		if (!args)
			return (-1);
	}
	else if (ac > 2)
	{
		args = av + 1;
	}
	else
	{
		return (0);
	}
	result = add_elements_to_stack(stack, args, ac);
	if (result == -1)
		return (-1);
	indexingstack(stack);
	if (ac == 2)
		ft_free_split(args);
	return (0);
}

void	sort_stack(t_list **stack_a, t_list **stack_b)
{
	if (ft_lstsize(*stack_a) <= 5)
		simple_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}
