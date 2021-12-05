/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:38:12 by chpl              #+#    #+#             */
/*   Updated: 2021/11/02 12:29:23 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/libs.h"

void	*spawn(void *arg)
{
	t_wrap			*wrap;
	t_simulation	*sim;
	int				index;

	wrap = (t_wrap *)arg;
	sim = wrap->data;
	index = wrap->index;
	experience_life(sim, index);
	return (0);
}

void	*start_waiter(void *arg)
{
	t_simulation	*sim;
	int				i;

	i = 0;
	sim = (t_simulation *)arg;
	while (i < sim->nb_philo)
		sim->waiter->queue[i++] = -1;
	waiter(sim);
	return (0);
}

void	*start_observer(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!pa_read_int(&sim->start_mut, &sim->start))
		NULL ;
	usleep(sim->tt_die_u / 2);
	observer(sim);
	return (0);
}

int	start_philosophers(t_simulation *sim, t_wrap *wrap)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		wrap[i].data = sim;
		sim->philosophers[i].last_ate = 0;
		wrap[i].index = i;
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				&spawn, &wrap[i]))
			return (1);
		i++;
	}
	return (0);
}

int	start_simulation(t_simulation *sim)
{
	sim->run = 1;
	sim->start = 0;
	sim->wrap = malloc(sizeof(t_wrap) * sim->nb_philo);
	pthread_mutex_init(&sim->start_in_ms_mut, NULL);
	if (start_philosophers(sim, sim->wrap))
		return (1);
	if (pthread_create(&sim->thr_waiter, NULL, &start_waiter, sim))
		return (1);
	if (pthread_create(&sim->thr_obs, NULL, &start_observer, sim))
		return (1);
	pa_write_ulong(&sim->start_in_ms_mut, &sim->start_in_ms, time_in_ms());
	pa_write_int(&sim->start_mut, &sim->start, 1);
	return (0);
}
