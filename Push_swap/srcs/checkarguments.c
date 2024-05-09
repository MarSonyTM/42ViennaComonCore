/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkarguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:01:17 by mafurnic          #+#    #+#             */
/*   Updated: 2023/11/29 13:49:03 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static	int	ft_contains(int num, char **av, int i)
{
	i++;
	while (av[i])
	{
		if (ft_atoi(av[i]) == num)
			return (1);
		i++;
	}
	return (0);
}

void	validate_arg(char *arg, char **args, int index, int flag)
{
	long	tmp;

	tmp = ft_atoi_long(arg);
	if (tmp > INT_MAX || tmp < INT_MIN)
	{
		if (flag == 1)
			ft_error_args("Error", args);
		else
			ft_error("Error");
	}
	if (!ft_isnum(arg) && flag == 0)
		ft_error("Error");
	else if (!ft_isnum(arg) && flag == 1)
		ft_error_args("Error", args);
	if (ft_contains(tmp, args, index))
	{
		if (flag == 1)
			ft_error_args("Error", args);
		else
			ft_error("Error");
	}
}

void	process_args(char **args, int count, int flag)
{
	int	i;

	i = 0;
	while (i < count)
	{
		validate_arg(args[i], args, i, flag);
		i++;
	}
}

int	ft_split_check(char *arg)
{
	char	**args;
	int		count;
	long	tmp;

	tmp = ft_atoi_long(arg);
	if (tmp > INT_MAX || tmp < INT_MIN)
		ft_error("Error");
	if (strchr(arg, ' ') == NULL)
	{
		if (!ft_isnum(arg))
			ft_error("Error");
		return (0);
	}
	if (ft_strlen(arg) == 1)
		ft_error("Error");
	args = ft_split(arg, ' ');
	if (!args)
		return (ft_free_split(args), -1);
	count = 0;
	while (args[count])
		count++;
	process_args(args, count, 1);
	ft_free_split(args);
	return (0);
}

void	ft_checkargs(int ac, char **av)
{
	if (ac < 2)
		ft_error("Error");
	check_alpha(av[1]);
	if (ac == 2)
	{
		if (ft_only_space(av[1]))
			ft_error("Error");
		ft_split_check(av[1]);
	}
	else
	{
		process_args(&av[1], ac - 1, 0);
	}
}
