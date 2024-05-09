/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:40:24 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/26 13:34:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define PHILO_MAX 200

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

// Program configuration (input)
typedef struct s_config
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_target;
}	t_config;

// Philosopher entity
typedef struct philosopher
{
	t_thread		life_thread;
	int				identity;
	int				is_eating;
	int				meal_count;
	size_t			last_meal_time;
	size_t			death_time;
	size_t			eat_duration;
	size_t			sleep_duration;
	size_t			epoch_start;
	int				total_philos;
	int				meals_target;
	int				*flag_dead;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_mutex			*output_lock;
	t_mutex			*death_lock;
	t_mutex			*meal_check_lock;
}	t_philosopher;

// Program state
typedef struct program_state
{
	int				flag_terminated;
	t_mutex			lock_death;
	t_mutex			lock_meal_check;
	t_mutex			lock_output;
	t_philosopher	*philosophers;
}	t_program_state;

// Philosopher initialization data
typedef struct s_philosopher_init_data
{
	t_program_state	*program;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_config		*config;
	size_t			current_millis;
}	t_philosopher_init_data;

// Argument validation
int		check_argument_content(char *arg);
int		validate_program_input(char **argv, t_config *config);

// Initialization
void	setup_philosophers(t_philosopher *philosophers,
			t_program_state *program, t_mutex *forks, t_config *config);
void	setup_forks(t_mutex *forks, int count);
void	setup_program(t_program_state *program, t_philosopher *philosophers);

// Thread management
int		create_all_philosopher_threads(t_program_state *program,
			t_mutex *forks);
int		join_all_philosopher_threads(t_program_state *program);
int		create_philosopher_threads(t_program_state *program, t_mutex *forks);
void	*monitor_routine(void *pointer);
void	*philosopher_routine(void *pointer);

// Philosopher actions
void	perform_eating(t_philosopher *philosopher);
void	perform_sleeping(t_philosopher *philosopher);
void	perform_thinking(t_philosopher *philosopher);

// Monitoring utilities
int		check_dead_flag(t_philosopher *philosopher);
int		check_if_all_philosophers_satisfied(t_philosopher *philosophers);
int		any_philosopher_died(t_philosopher *philosophers);
int		validate_philosopher_death(t_philosopher *philosopher,
			size_t max_lifetime);

// General utilities
int		convert_to_int(char *str);
int		sleep_for_microseconds(size_t microseconds);
int		ft_strlen(char *str);
void	print_status(char *str, t_philosopher *philosopher, int id);
void	clean_resources(char *msg, t_program_state *program, t_mutex *forks);
size_t	current_time_millis(void);

#endif
