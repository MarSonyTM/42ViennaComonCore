/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:39:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/04 12:44:06 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Think routine function
void	perform_thinking(t_philosopher *philosopher)
{
	print_status("is thinking", philosopher, philosopher->identity);
}

// Dream (sleep) routine function
void	perform_sleeping(t_philosopher *philosopher)
{
	print_status("is sleeping", philosopher, philosopher->identity);
	sleep_for_microseconds(philosopher->sleep_duration);
}

// Eat routine function
void	perform_eating(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	print_status("has taken a fork", philosopher, philosopher->identity);
	if (philosopher->total_philos == 1)
	{
		sleep_for_microseconds(philosopher->death_time);
		pthread_mutex_unlock(philosopher->right_fork);
		return ;
	}
	pthread_mutex_lock(philosopher->left_fork);
	print_status("has taken a fork", philosopher, philosopher->identity);
	philosopher->is_eating = 1;
	print_status("is eating", philosopher, philosopher->identity);
	pthread_mutex_lock(philosopher->meal_check_lock);
	philosopher->last_meal_time = current_time_millis();
	philosopher->meal_count++;
	pthread_mutex_unlock(philosopher->meal_check_lock);
	sleep_for_microseconds(philosopher->eat_duration);
	philosopher->is_eating = 0;
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}
