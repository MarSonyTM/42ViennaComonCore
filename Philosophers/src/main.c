/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:04:54 by mafurnic          #+#    #+#             */
/*   Updated: 2024/01/04 17:14:14 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_program_state	program;
	t_philosopher	*philosophers;
	t_mutex			*forks;
	t_config		config;

	if (argc != 5 && argc != 6)
	{
		printf("\tWrong number of arguments\n");
		return (printf("./philo nb_of_phil t_to_die t_to_eat t_to_sleep\n"), 1);
	}
	if (validate_program_input(argv, &config) == 1)
		return (1);
	philosophers = malloc(sizeof(t_philosopher) * config.num_philosophers);
	forks = malloc(sizeof(t_mutex) * config.num_philosophers);
	if (philosophers == NULL || forks == NULL)
		return (printf("Failed to allocate memory\n"), 1);
	setup_program(&program, philosophers);
	setup_forks(forks, config.num_philosophers);
	setup_philosophers(philosophers, &program, forks, &config);
	create_philosopher_threads(&program, forks);
	clean_resources(NULL, &program, forks);
	free(philosophers);
	free(forks);
	return (0);
}
