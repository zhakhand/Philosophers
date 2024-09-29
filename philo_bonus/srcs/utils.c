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

#include "../include/philo_bonus.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

long long	get_ctime(t_info *info)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((((long long)t.tv_sec * 1000) + \
	((long long)t.tv_usec / 1000)) - (long long)info->start);
}

long long	ft_usleep(long long ms, t_info *info)
{
	int	s_time;

	s_time = get_ctime(info);
	while (get_ctime(info) - s_time < ms)
		usleep(100);
	return (0);
}
