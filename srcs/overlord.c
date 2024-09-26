/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:40:37 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 17:09:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	all_ate(t_info *info)
{
	int		i;
	int		count;
	t_philo	*philos;

	philos = info->philos;
	i = -1;
	count = 0;
	while (++i < info->philo_num && philos[i].num_to_eat != -1)
	{
		if (philos[i].meals_eaten >= philos[i].num_to_eat)
			count++;
	}
	if (count == info->philo_num)
		info->all_full = 1;
}

void	overlord(t_info *info)
{
	int		i;
	int		k;
	t_philo *philos;

	philos = info->philos;
	while (!info->all_full)
	{
		i = -1;
		while (++i < info->philo_num && !info->one_dead)
		{
			pthread_mutex_lock(&info->is_eating);
			if (get_ctime() - philos[i].last_meal > philos[i].time_to_die)
			{
				is_doing("has died\n", &philos[i]);
				info->one_dead = 1;
				k = -1;
				while (++k < info->philo_num)
					pthread_mutex_unlock(&info->forks[k]);
			}
			pthread_mutex_unlock(&info->is_eating);
			usleep(500);
		}
			if (info->one_dead)
				break ;
			all_ate(info);
	}
}