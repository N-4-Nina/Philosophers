/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:53:27 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/02 12:12:01 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/simulation.h"
#include "../include/utils.h"

int	isanumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	if (i > 10)
		return (printf("All parameters should be inferior to INT_MAX.\n") * 0);
	return (1);
}

int	check_and_convert(char *param, int *result)
{
	if (!isanumber(param))
		return (1);
	*result = ft_atoi(param);
	if (*result < 0)
		return (printf("All parameters should be inferior to INT_MAX.\n"));
	return (0);
}

int	parse_args(int argc, char **argv, t_simulation *sim)
{
	int	i;
	int	args[5];

	i = 1;
	if (argc < 5 || argc > 6)
		return (-1);
	while (i < argc)
	{
		if (check_and_convert(argv[i], &args[i - 1]))
			return (1);
		i++;
	}
	sim->nb_philo = args[0];
	sim->tt_die = args[1];
	sim->tt_eat = args[2];
	sim->tt_sleep = args[3];
	sim->tt_die_u = sim->tt_die * 1000;
	sim->tt_eat_u = sim->tt_eat * 1000;
	sim->tt_sleep_u = sim->tt_sleep * 1000;
	if (argc == 6)
		sim->must_eat = args[4];
	else
		sim->must_eat = -1;
	return (init_sim(sim));
}
