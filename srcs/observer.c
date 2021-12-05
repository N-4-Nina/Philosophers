/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:08:18 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 13:12:30 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/simulation.h"
#include "../include/utils.h"

int	reached_must_eat(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		if (!(pa_read_int(&sim->philosophers[i].sated_mut,
					&sim->philosophers[i].sated)))
			return (0);
		i++;
	}
	pa_write_int(&sim->run_mut, &sim->run, 0);
	usleep(100);
	printf("All philosophers ate %d times\n", sim->must_eat);
	return (1);
}

void	observer(t_simulation *sim)
{
	int				i;
	unsigned long	now;
	unsigned long	tt_die;

	i = 0;
	tt_die = (unsigned long)sim->tt_die;
	while (pa_read_int(&sim->run_mut, &sim->run))
	{
		if (sim->must_eat != -1 && reached_must_eat(sim))
			break ;
		now = time_in_ms();
		if (now > pa_read_ulong(&sim->philosophers[i].last_ate_mut,
				&sim->philosophers[i].last_ate) + tt_die)
		{
			sim->philosophers[i].status = ISDEAD;
			log_status(sim, i, ISDEAD);
			pa_write_int(&sim->run_mut, &sim->run, 0);
		}
		i++;
		if (i == sim->nb_philo)
			i = 0;
		usleep(500);
	}
	return ;
}
