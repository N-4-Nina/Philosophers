/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:23:07 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 13:17:52 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/libs.h"

int	philo_sleep(t_simulation *sim, int index, t_philo *philo)
{
	log_status(sim, index, ISSLEEPING);
	phi_pause(sim->tt_sleep, sim);
	philo->status = THINKING;
	return (0);
}

int	philo_think(t_simulation *sim, int index, t_philo *philo)
{
	log_status(sim, index, ISTHINKING);
	pa_write_int(&philo->req_mut, &philo->req, 1);
	while (!pa_read_int(&philo->authorize_mut, &philo->authorize))
	{
		usleep(500);
		if (!pa_read_int(&sim->run_mut, &sim->run))
			return (1);
	}
	philo->authorize = 0;
	log_status(sim, index, FORK);
	log_status(sim, index, FORK);
	philo->status = EATING;
	return (0);
}

int	philo_think_offset(t_simulation *sim, int index, t_philo *philo)
{
	philo->offset = 0;
	phi_pause(sim->tt_eat / 2 + 1, sim);
	return (philo_think(sim, index, philo));
}

int	philo_eat(t_simulation *sim, int index, t_philo *philo)
{
	pa_write_ulong(&philo->last_ate_mut, &philo->last_ate, time_in_ms());
	log_status(sim, index, ISEATING);
	phi_pause(sim->tt_eat, sim);
	pa_write_int(&philo->lfork->mut, &philo->lfork->held, 0);
	pa_write_int(&philo->rfork->mut, &philo->rfork->held, 0);
	philo->nb_ate++;
	if (philo->nb_ate == sim->must_eat)
		pa_write_int(&philo->sated_mut, &philo->sated, 1);
	philo->status = SLEEPING;
	return (0);
}
