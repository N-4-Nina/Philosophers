/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:38:48 by chpl              #+#    #+#             */
/*   Updated: 2021/11/02 12:29:07 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/libs.h"

void	free_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < 5)
		free(sim->logs[i++]);
	free(sim->logs);
	free(sim->philosophers);
	free(sim->waiter->queue);
	free(sim->waiter);
	free(sim->forks);
	free(sim->wrap);
}

void	wait_for_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_join(sim->thr_waiter, NULL);
	pthread_join(sim->thr_obs, NULL);
	while (i < sim->nb_philo)
		pthread_join(sim->philosophers[i++].thread, NULL);
	free_simulation(sim);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (parse_args(argc, argv, &simulation))
		return (printf("Error: invalid arguments\n") - 25);
	if (start_simulation(&simulation))
	{
		simulation.run = 0;
		simulation.start = 1;
		printf("Error: Failed to create a thread, \
number of philosophers must be too high !\n");
	}
	wait_for_threads(&simulation);
	return (0);
}
