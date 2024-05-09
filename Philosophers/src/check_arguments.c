/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:02 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/26 13:34:30 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atoi_long(const char *nptr)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (*nptr == '+' || *nptr == '-')
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

// Checks if a given argument string is numeric
int	check_argument_content(char *argv)
{
	if (*argv == '+')
		argv++;
	while (*argv)
	{
		if (*argv < '0' || *argv > '9')
			return (1);
		argv++;
	}
	return (0);
}

int	validate_numeric_argument(char *arg, int min, int max,
		const char *error_msg)
{
	long	value;

	if (check_argument_content(arg) == 1)
		return (printf("%s\n", error_msg), 1);
	value = ft_atoi_long(arg);
	if (value > INT_MAX || value < INT_MIN)
		return (printf("Value out of int range\n"), 1);
	if (value < min || (max != -1 && value > max))
		return (printf("%s\n", error_msg), 1);
	return (0);
}

int	validate_optional_meals_argument(char *argv)
{
	if (argv == NULL)
		return (0);
	return (validate_numeric_argument(argv, 0, -1, "Invalid number"));
}

int	validate_program_input(char **argv, t_config *config)
{
	if (validate_numeric_argument(argv[1], 1, PHILO_MAX,
			"Invalid philosophers number")
		|| validate_numeric_argument(argv[2], 1, -1, "Invalid time to die")
		|| validate_numeric_argument(argv[3], 1, -1, "Invalid time to eat")
		|| validate_numeric_argument(argv[4], 1, -1, "Invalid time to sleep")
		|| validate_optional_meals_argument(argv[5]))
		return (1);
	config->num_philosophers = convert_to_int(argv[1]);
	config->time_to_die = convert_to_int(argv[2]);
	config->time_to_eat = convert_to_int(argv[3]);
	config->time_to_sleep = convert_to_int(argv[4]);
	if (argv[5])
		config->meals_target = convert_to_int(argv[5]);
	else
		config->meals_target = -1;
	return (0);
}
