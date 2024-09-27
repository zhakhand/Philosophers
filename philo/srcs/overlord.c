/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:40:37 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 18:40:38 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	all_ate(t_info *info)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&info->is_eating);
	while (info->philos[i].num_to_eat != -1 && i < info->philo_num)
	{
		if (info->philos[i].meals_eaten >= info->philos[i].num_to_eat)
			count++;
		i++;
	}
	if (count == info->philo_num)
		info->all_full = 1; // create a mutex for this?
	pthread_mutex_unlock(&info->is_eating);
}
//try creating a mutx for full and dead
void	overlord(t_info *info)
{
	int		i;
	t_philo	*philos;

	philos = info->philos;
	while (!info->all_full)
	{
		i = -1;
		while (++i < info->philo_num && !info->one_dead)
		{
			pthread_mutex_lock(&info->is_eating);
			if (get_ctime(info) - philos[i].last_meal > \
			philos[i].time_to_die && !philos[i].is_eating)
			{
				is_doing("died", &philos[i]);
				info->one_dead = 1; //this too?
				pthread_mutex_unlock(&info->is_eating);
				break ;
			}
			pthread_mutex_unlock(&info->is_eating);
		}
		if (info->one_dead)
			break ;
		all_ate(info);
	}
}
