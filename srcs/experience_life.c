/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experience_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:50:56 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 13:18:46 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/actions.h"
#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/libs.h"

int	lonely_life(t_simulation *sim)
{
	log_status(sim, 0, ISTHINKING);
	log_status(sim, 0, FORK);
	phi_pause(sim->tt_sleep, sim);
	return (0);
}

int	experience_life(t_simulation *sim, int index)
{
	t_philo	*philo;

	philo = &sim->philosophers[index];
	while (!pa_read_int(&sim->start_mut, &sim->start))
		usleep(500);
	pa_write_ulong(&philo->last_ate_mut, &philo->last_ate,
		pa_read_ulong(&sim->start_in_ms_mut, &sim->start_in_ms));
	if (sim->nb_philo == 1)
		return (lonely_life(sim));
	if (philo->offset && pa_read_int(&sim->run_mut, &sim->run))
		philo_think_offset(sim, index, philo);
	while (pa_read_int(&sim->run_mut, &sim->run))
		sim->actions[philo->status](sim, index, philo);
	return (0);
}
