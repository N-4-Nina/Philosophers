/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:30:18 by abouchau          #+#    #+#             */
/*   Updated: 2021/10/31 16:22:42 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "libs.h"
# include "actual_fork.h"

enum	e_log
{
	ISDEAD,
	ISEATING,
	ISSLEEPING,
	ISTHINKING,
	FORK
};

enum	e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING
};

typedef struct s_philo
{
	int				nb;
	int				status;
	int				authorize;
	int				req;
	int				sated;
	int				nb_ate;
	int				offset;
	t_afork			*lfork;
	t_afork			*rfork;
	unsigned long	last_ate;
	pthread_t		thread;
	pthread_mutex_t	sated_mut;
	pthread_mutex_t	last_ate_mut;
	pthread_mutex_t	authorize_mut;
	pthread_mutex_t	req_mut;
}				t_philo;

#endif
