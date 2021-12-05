/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:22:07 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/02 12:24:17 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "philosopher.h"
# include "actual_fork.h"
# include "waiter.h"

typedef struct s_wrap	t_wrap;
typedef struct s_sim	t_simulation;

typedef struct s_sim
{
	unsigned long	start_in_ms;
	int				run;
	int				start;
	int				nb_philo;
	int				must_eat;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	unsigned int	tt_die_u;
	unsigned int	tt_eat_u;
	unsigned int	tt_sleep_u;
	t_philo			*philosophers;
	pthread_t		thr_waiter;
	pthread_t		thr_obs;
	t_waiter		*waiter;
	pthread_mutex_t	write_mut;
	pthread_mutex_t	run_mut;
	pthread_mutex_t	start_mut;
	pthread_mutex_t	start_in_ms_mut;
	char			**logs;
	t_afork			*forks;
	t_wrap			*wrap;
	int				(*actions[4])(t_simulation *sim, int index, t_philo *philo);
}					t_simulation;

typedef struct s_wrap
{
	int				index;
	struct s_sim	*data;
}				t_wrap;

void	waiter(t_simulation *sim);
void	observer(t_simulation *sim);
int		experience_life(t_simulation *sim, int index);
int		start_simulation(t_simulation *sim);

#endif