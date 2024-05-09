/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:00:05 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/05 13:02:14 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_single_philosopher(t_philosopher *philosopher,
		t_philosopher_init_data *init_data)
{
	philosopher->is_eating = 0;
	philosopher->meal_count = 0;
	philosopher->death_time = init_data->config->time_to_die;
	philosopher->eat_duration = init_data->config->time_to_eat;
	philosopher->sleep_duration = init_data->config->time_to_sleep;
	philosopher->total_philos = init_data->config->num_philosophers;
	philosopher->meals_target = init_data->config->meals_target;
	philosopher->epoch_start = init_data->current_millis;
	philosopher->last_meal_time = init_data->current_millis;
	philosopher->output_lock = &init_data->program->lock_output;
	philosopher->death_lock = &init_data->program->lock_death;
	philosopher->meal_check_lock = &init_data->program->lock_meal_check;
	philosopher->flag_dead = &init_data->program->flag_terminated;
	philosopher->left_fork = init_data->left_fork;
	philosopher->right_fork = init_data->right_fork;
}

void	setup_philosophers(t_philosopher *philosophers,
		t_program_state *program, t_mutex *forks, t_config *config)
{
	int						i;
	size_t					current_millis;
	t_philosopher_init_data	init_data;

	i = 0;
	current_millis = current_time_millis();
	while (i < config->num_philosophers)
	{
		init_data.program = program;
		init_data.left_fork = &forks[i];
		init_data.config = config;
		init_data.current_millis = current_millis;
		if (i == 0)
			init_data.right_fork = &forks[config->num_philosophers - 1];
		else
			init_data.right_fork = &forks[i - 1];
		philosophers[i].identity = i + 1;
		init_single_philosopher(&philosophers[i], &init_data);
		i++;
	}
}

// Initializing the forks (mutexes)
void	setup_forks(t_mutex *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

// Initializing the program structure
void	setup_program(t_program_state *program, t_philosopher *philosophers)
{
	program->flag_terminated = 0;
	program->philosophers = philosophers;
	pthread_mutex_init(&program->lock_output, NULL);
	pthread_mutex_init(&program->lock_death, NULL);
	pthread_mutex_init(&program->lock_meal_check, NULL);
}
