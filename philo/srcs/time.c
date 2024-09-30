/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:19:52 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:32:31 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/******************************************/
/*would be a good practice to also protect*/
/*     gettimeofday(t, *) with mutexes    */
/* to prevent threads accessing it at once*/
/*(though it doesn't make much difference)*/
/**************************************** */

void	safe_gettime(struct timeval *t, t_info *info)
{
	pthread_mutex_lock(&info->time_mut);
	gettimeofday(t, NULL);
	pthread_mutex_unlock(&info->time_mut);
}

long long	get_ctime(t_info *info)
{
	struct timeval	t;

	safe_gettime(&t, info);
	return ((((long long)t.tv_sec * 1000) + \
	((long long)t.tv_usec / 1000)) - (long long)info->start);
}

long long	ft_usleep(long long milliseconds, t_info *info)
{
	int	start_time;

	start_time = get_ctime(info);
	while (get_ctime(info) - start_time < milliseconds)
		usleep(100);
	return (0);
}
