/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:24:22 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 12:08:10 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/simulation.h"
#include "../include/actions.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

void	load_logs(t_simulation *sim)
{
	sim->logs = malloc(sizeof(char *) * 5);
	sim->logs[ISDEAD] = ft_strdup(" died\n");
	sim->logs[ISEATING] = ft_strdup(" is eating\n");
	sim->logs[ISSLEEPING] = ft_strdup(" is sleeping\n");
	sim->logs[ISTHINKING] = ft_strdup(" is thinking\n");
	sim->logs[FORK] = ft_strdup(" has taken a fork\n");
}

int	allocate(t_simulation *sim)
{
	sim->philosophers = malloc((sizeof(t_philo) + 1) * sim->nb_philo);
	if (!sim->philosophers)
		return (-1);
	sim->waiter = malloc(sizeof(t_waiter));
	if (!sim->waiter)
		return (-1);
	sim->waiter->queue = malloc(sizeof(int) * sim->nb_philo + 1);
	if (!sim->waiter->queue)
		return (-1);
	sim->forks = malloc(sizeof(t_afork) * (sim->nb_philo + 1));
	if (!sim->forks)
		return (-1);
	return (0);
}

void	init_philo(t_simulation *sim, int i)
{
	sim->philosophers[i].status = THINKING;
	sim->philosophers[i].nb = i + 1;
	sim->philosophers[i].lfork = &(sim->forks[i]);
	if (i < sim->nb_philo - 1)
		sim->philosophers[i].rfork = &(sim->forks[i + 1]);
	sim->philosophers[i].authorize = 0;
	sim->philosophers[i].sated = 0;
	sim->philosophers[i].req = 0;
	sim->philosophers[i].nb_ate = 0;
	sim->waiter->queue[i] = -1;
	sim->philosophers[i].offset = 0;
	if (i % 2)
		sim->philosophers[i].offset = 1;
	pthread_mutex_init(&sim->philosophers[i].last_ate_mut, NULL);
	pthread_mutex_init(&sim->philosophers[i].sated_mut, NULL);
	pthread_mutex_init(&sim->philosophers[i].authorize_mut, NULL);
	pthread_mutex_init(&sim->philosophers[i].req_mut, NULL);
}

int	init_sim(t_simulation *sim)
{
	int	i;

	i = 0;
	if (allocate(sim))
		return (-1);
	sim->waiter->queue_size = 0;
	while (i < sim->nb_philo)
	{
		pthread_mutex_init(&sim->forks[i].mut, NULL);
		sim->forks[i].last = -1;
		sim->forks[i++].held = 0;
	}
	i = 0;
	while (i < sim->nb_philo)
		init_philo(sim, i++);
	sim->philosophers[i - 1].rfork = &sim->forks[0];
	pthread_mutex_init(&sim->write_mut, NULL);
	pthread_mutex_init(&sim->run_mut, NULL);
	pthread_mutex_init(&sim->start_mut, NULL);
	sim->actions[ISDEAD] = NULL;
	sim->actions[ISEATING] = &philo_eat;
	sim->actions[ISSLEEPING] = &philo_sleep;
	sim->actions[ISTHINKING] = &philo_think;
	load_logs(sim);
	return (0);
}
