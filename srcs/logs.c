/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:34:59 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 14:03:18 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"
#include "../include/simulation.h"
#include "../include/utils.h"
#include "../include/libs.h"

int	get_size(long n)
{
	int				size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n > 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*get_converted_str(char *str, long res, int *i)
{
	if (res >= 10)
		get_converted_str(str, res / 10, i);
	str[(*i)++] = res % 10 + '0';
	return (str);
}

char	*build_log(t_simulation *sim, int index, int status, long now)
{
	char	*str;
	int		i;
	int		sizes[4];

	i = 0;
	sizes[0] = get_size(now);
	sizes[1] = get_size((long)index);
	sizes[2] = ft_strlen(sim->logs[status]);
	sizes[3] = sizes[0] + sizes[1] + sizes[2] + 9;
	str = malloc(sizes[3]);
	memset(str, 0, sizes[3]);
	get_converted_str(str, now, &i);
	ft_strlcat(str + sizes[0], " ms : ", sizes[3]);
	i = 0;
	get_converted_str(str + sizes[0] + 6, (long)index, &i);
	ft_strlcat(str + sizes[0] + sizes[1] + 6, " ", sizes[3]);
	ft_strlcat(str + sizes[0] + sizes[1] + 7, sim->logs[status], sizes[3]);
	return (str);
}

void	log_status(t_simulation *sim, int index, int status)
{	
	char	*str;

	pthread_mutex_lock(&sim->write_mut);
	str = build_log(sim, index + 1, status, time_in_ms() - sim->start_in_ms);
	if (!pa_read_int(&sim->run_mut, &sim->run))
	{
		pthread_mutex_unlock(&sim->write_mut);
		free(str);
		return ;
	}
	write(1, str, ft_strlen(str));
	free(str);
	pthread_mutex_unlock(&sim->write_mut);
}
