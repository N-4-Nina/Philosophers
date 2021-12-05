/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:18:59 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 13:07:39 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "simulation.h"

int				ft_atoi(const char *str);
void			ft_putnbr(int n, char *buf, int *i);
void			ft_putlong(unsigned long n, char **ptr);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				parse_args(int argc, char **argv, t_simulation *sim);
int				init_sim(t_simulation *sim);

unsigned long	time_in_ms(void);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
void			log_status(t_simulation *sim, int index, int status);
void			phi_pause(unsigned int tt_pause, t_simulation *sim);
void			pa_write_int(pthread_mutex_t *mut, int *data, int value);
int				pa_read_int(pthread_mutex_t *mut, int *data);
unsigned long	pa_read_ulong(pthread_mutex_t *mut, unsigned long *data);
void			pa_write_ulong(pthread_mutex_t *mut,
					unsigned long *data, unsigned long value);

#endif