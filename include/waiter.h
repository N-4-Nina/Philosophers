/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:16:57 by abouchau          #+#    #+#             */
/*   Updated: 2021/10/29 14:18:40 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAITER_H
# define WAITER_H

# include <pthread.h>

typedef struct s_waiter
{
	int	*queue;
	int	queue_size;
}				t_waiter;

#endif