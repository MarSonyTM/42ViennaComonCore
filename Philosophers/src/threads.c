/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:39:25 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/04 13:03:40 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Checks if the value of flag_dead changed
int	check_dead_flag(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->death_lock);
	if (*philosopher->flag_dead == 1)
	{
		pthread_mutex_unlock(philosopher->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philosopher->death_lock);
	return (0);
}

// Philosopher routine
void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)pointer;
	if (philosopher->identity % 2 == 0)
		sleep_for_microseconds(1);
	while (!check_dead_flag(philosopher))
	{
		perform_eating(philosopher);
		perform_sleeping(philosopher);
		perform_thinking(philosopher);
	}
	return (pointer);
}

// Creates all the threads
// Helper function to create all philosopher threads
int	create_all_philosopher_threads(t_program_state *program, t_mutex *forks)
{
	int	i;

	i = 0;
	while (i < program->philosophers[0].total_philos)
	{
		if (pthread_create(&program->philosophers[i].life_thread,
				NULL, &philosopher_routine, &program->philosophers[i]) != 0)
		{
			clean_resources("Failed to create philosopher thread",
				program, forks);
			return (-1);
		}
		i++;
	}
	return (0);
}

// Helper function to join all philosopher threads
int	join_all_philosopher_threads(t_program_state *program)
{
	int	i;

	i = 0;
	while (i < program->philosophers[0].total_philos)
	{
		if (pthread_join(program->philosophers[i].life_thread, NULL) != 0)
		{
			clean_resources("Failed to join philosopher thread", program, NULL);
			return (-1);
		}
		i++;
	}
	return (0);
}

// Main function to create and manage philosopher threads
int	create_philosopher_threads(t_program_state *program, t_mutex *forks)
{
	pthread_t	observer;

	if (pthread_create(&observer, NULL,
			&monitor_routine, program->philosophers) != 0)
	{
		clean_resources("Failed to create observer thread", program, forks);
		return (-1);
	}
	if (create_all_philosopher_threads(program, forks) != 0)
		return (-1);
	if (pthread_join(observer, NULL) != 0)
	{
		clean_resources("Failed to join observer thread", program, forks);
		return (-1);
	}
	if (join_all_philosopher_threads(program) != 0)
		return (-1);
	return (0);
}
