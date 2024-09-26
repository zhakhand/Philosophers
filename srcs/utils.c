/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:32 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 18:40:29 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

long long	get_ctime(void)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	return (((long long)t.tv_sec * 1000) + ((long long)t.tv_usec / 1000));
}

long long	ft_usleep(long long ms)
{
	int	s_time;

	s_time = get_ctime();
	while (get_ctime() - s_time < ms)
		usleep(500);
	return (0);
}