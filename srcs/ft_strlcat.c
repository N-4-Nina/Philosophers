/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:20:18 by abouchau          #+#    #+#             */
/*   Updated: 2021/11/01 13:08:26 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libs.h"
#include "../include/utils.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dest_count;
	unsigned int	src_count;

	dest_count = ft_strlen(dest);
	src_count = ft_strlen(src);
	if (size < 1)
		return (src_count);
	if (size < dest_count)
		return (src_count + size);
	i = 0;
	while (src[i] && i + dest_count < size - 1)
	{
		dest[dest_count + i] = src[i];
		i++;
	}
	dest[dest_count + i] = '\0';
	return (dest_count + src_count);
}
