/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:38:49 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/04 12:40:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Print message function
void	print_status(char *str, t_philosopher *philosopher, int id)
{
	size_t	time;

	pthread_mutex_lock(philosopher->output_lock);
	time = current_time_millis() - philosopher->epoch_start;
	if (!check_dead_flag(philosopher))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philosopher->output_lock);
}

// Checks if the philosopher is dead
int	validate_philosopher_death(t_philosopher *philosopher, size_t max_lifetime)
{
	pthread_mutex_lock(philosopher->meal_check_lock);
	if (current_time_millis() - philosopher->last_meal_time >= max_lifetime
		&& philosopher->is_eating == 0)
	{
		pthread_mutex_unlock(philosopher->meal_check_lock);
		return (1);
	}
	pthread_mutex_unlock(philosopher->meal_check_lock);
	return (0);
}

// Check if any philosopher died
int	any_philosopher_died(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0].total_philos)
	{
		if (validate_philosopher_death(&philosophers[i],
				philosophers[i].death_time))
		{
			print_status("died", &philosophers[i], philosophers[i].identity);
			pthread_mutex_lock(philosophers[0].death_lock);
			*philosophers->flag_dead = 1;
			pthread_mutex_unlock(philosophers[0].death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philosophers ate the required number of meals
int	check_if_all_philosophers_satisfied(t_philosopher *philosophers)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philosophers[0].meals_target == -1)
		return (0);
	while (i < philosophers[0].total_philos)
	{
		pthread_mutex_lock(philosophers[i].meal_check_lock);
		if (philosophers[i].meal_count >= philosophers[i].meals_target)
			finished_eating++;
		pthread_mutex_unlock(philosophers[i].meal_check_lock);
		i++;
	}
	if (finished_eating == philosophers[0].total_philos)
	{
		pthread_mutex_lock(philosophers[0].death_lock);
		*philosophers->flag_dead = 1;
		pthread_mutex_unlock(philosophers[0].death_lock);
		return (1);
	}
	return (0);
}

// Monitor thread routine
void	*monitor_routine(void *pointer)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)pointer;
	while (1)
	{
		if (any_philosopher_died(philosophers) == 1
			|| check_if_all_philosophers_satisfied(philosophers) == 1)
			break ;
	}
	return (pointer);
}
