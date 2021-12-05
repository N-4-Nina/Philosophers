/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:06:25 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/02 11:25:19 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libs.h"
#include "../include/simulation.h"
#include "../include/utils.h"

unsigned long	time_in_ms(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	phi_pause(unsigned int tt_pause, t_simulation *sim)
{
	unsigned long	wakeup;
	long			diff;

	wakeup = time_in_ms() + (unsigned long)tt_pause;
	diff = wakeup - time_in_ms();
	while (diff > 0 && pa_read_int(&sim->run_mut, &sim->run))
	{
		usleep(diff / 2 + sim->nb_philo);
		diff = wakeup - time_in_ms();
	}
}
