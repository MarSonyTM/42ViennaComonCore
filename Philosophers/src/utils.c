/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:39:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/05 16:06:25 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Checks the length of the string
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

// Own version of atoi
int	convert_to_int(char *str)
{
	int					sign;
	unsigned long long	nb;

	sign = 1;
	nb = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (sign * nb);
}

// Destroys all the mutexes
void	clean_resources(char *str, t_program_state *program, t_mutex *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->lock_output);
	pthread_mutex_destroy(&program->lock_meal_check);
	pthread_mutex_destroy(&program->lock_death);
	while (i < program->philosophers[0].total_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

// Improved version of sleep function
int	sleep_for_microseconds(size_t milliseconds)
{
	size_t	start;

	start = current_time_millis();
	while ((current_time_millis() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Gets the current time in milliseconds
size_t	current_time_millis(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
