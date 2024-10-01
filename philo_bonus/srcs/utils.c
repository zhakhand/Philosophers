/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:32 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 15:04:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(char const *str)
{
	int		result;
	int		sign;
	long	last;

	result = 0;
	sign = 1;
	last = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		if (last != (last * 10 + *str - '0') / 10)
			return ((sign >= 0) * -1);
		last = last * 10 + *str - '0';
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

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

long long	ft_usleep(long long milliseconds, t_info *info)
{
	int	s_time;

	s_time = get_ctime(info);
	while (get_ctime(info) - s_time < milliseconds)
		usleep(100);
	return (0);
}
