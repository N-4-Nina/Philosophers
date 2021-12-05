/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_acces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 11:40:29 by abouchau          #+#    #+#             */
/*   Updated: 2021/10/29 14:13:06 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libs.h"

void	pa_write_int(pthread_mutex_t *mut, int *data, int value)
{
	pthread_mutex_lock(mut);
	*(data) = value;
	pthread_mutex_unlock(mut);
}

int	pa_read_int(pthread_mutex_t *mut, int *data)
{
	int	ret;

	pthread_mutex_lock(mut);
	ret = *data;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	pa_write_ulong(pthread_mutex_t *mut,
		unsigned long *data, unsigned long value)
{
	pthread_mutex_lock(mut);
	*(data) = value;
	pthread_mutex_unlock(mut);
}

unsigned long	pa_read_ulong(pthread_mutex_t *mut, unsigned long *data)
{
	unsigned long	ret;

	pthread_mutex_lock(mut);
	ret = *data;
	pthread_mutex_unlock(mut);
	return (ret);
}
