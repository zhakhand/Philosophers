/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:32 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/25 16:23:46 by dzhakhan         ###   ########.fr       */
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

int	get_ctime(void)
{
	struct timeval t;
	
	if (gettimeofday(&t, NULL) == -1)
		printf("Wrong time!\n");
	return ((long long)t.tv_sec * 1000 + (long long)t.tv_usec / 1000);
}

int	ft_usleep(int ms)
{
	int	s_time;

	s_time = get_ctime();
	while (get_ctime() - s_time < ms)
		usleep(500);
	return (0);
}