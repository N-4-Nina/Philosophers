/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:23:55 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 10:17:46 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "../include/philosopher.h"
# include "../include/simulation.h"

int	philo_sleep(t_simulation *sim, int index, t_philo *philo);
int	philo_eat(t_simulation *sim, int index, t_philo *philo);
int	philo_think(t_simulation *sim, int index, t_philo *philo);
int	philo_think_offset(t_simulation *sim, int index, t_philo *philo);

#endif