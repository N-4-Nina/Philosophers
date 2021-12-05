/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_fork.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:24:32 by abouchau          #+#    #+#             */
/*   Updated: 2021/10/30 14:40:18 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTUAL_FORK_H
# define ACTUAL_FORK_H

# include <pthread.h>

typedef struct s_actual_fork
{
	int				held;
	int				last;
	pthread_mutex_t	mut;
}				t_afork;

#endif
