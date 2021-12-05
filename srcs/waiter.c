/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:11:25 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 10:29:58 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"

int	need_and_can_eat(t_philo *philo, int i)
{
	return (pa_read_int(&philo->req_mut, &philo->req)
		&& philo->rfork->last != i && philo->lfork->last != i
		&& !pa_read_int(&philo->lfork->mut, &philo->lfork->held)
		&& !pa_read_int(&philo->rfork->mut, &philo->rfork->held));
}

int	find_most_urgent(t_simulation *sim)
{
	int		i;
	int		select;
	t_philo	*philo;

	i = -1;
	select = -1;
	while (++i < sim->nb_philo)
	{
		philo = &sim->philosophers[i];
		if (need_and_can_eat(philo, i))
		{
			if (select > -1)
			{
				if (philo->last_ate < sim->philosophers[select].last_ate)
					select = i;
			}
			else
				select = i;
		}
	}
	return (select);
}

void	attend_request(t_simulation *sim, int index)
{
	t_philo	*philo;

	philo = &sim->philosophers[index];
	philo->req = 0;
	philo->lfork->last = index;
	philo->rfork->last = index;
	pa_write_int(&philo->lfork->mut, &philo->lfork->held, 1);
	pa_write_int(&philo->rfork->mut, &philo->rfork->held, 1);
	pa_write_int(&philo->authorize_mut, &philo->authorize, 1);
}

void	waiter(t_simulation *sim)
{
	int	index;

	index = -1;
	while (pa_read_int(&sim->run_mut, &sim->run))
	{
		index = find_most_urgent(sim);
		if (index > -1 && pa_read_int(&sim->run_mut, &sim->run))
			attend_request(sim, index);
		usleep(100);
	}
}
