/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:40:37 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:05:49 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/****************************************/
/*Each mutable value should be locked!!!*/
/****************************************/

int	experiment_ended(t_info *info)
{
	int	end;

	pthread_mutex_lock(&info->is_finished);
	end = (info->all_full || info->one_dead);
	return (pthread_mutex_unlock(&info->is_finished), end);
}

void	all_ate(t_info *info)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&info->is_eating);
	while (info->meal_goal != -1 && i < info->philo_num)
	{
		if (info->philos[i].meals_eaten >= info->meal_goal)
			count++;
		i++;
	}
	if (count == info->philo_num)
	{
		pthread_mutex_lock(&info->is_finished);
		info->all_full = 1;
		pthread_mutex_unlock(&info->is_finished);
	}
	pthread_mutex_unlock(&info->is_eating);
}

int	check_for_death(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num && !info->one_dead)
	{
		pthread_mutex_lock(&info->is_eating);
		if (get_ctime(info) - info->philos[i].last_meal > \
		info->philos[i].time_to_die && !info->philos[i].is_eating)
		{
			is_doing("died", &info->philos[i]);
			pthread_mutex_lock(&info->is_finished);
			info->one_dead = 1;
			pthread_mutex_unlock(&info->is_finished);
			pthread_mutex_unlock(&info->is_eating);
			return (1);
		}
		pthread_mutex_unlock(&info->is_eating);
	}
	return (0);
}

void	overseer(t_info *info)
{
	while (!info->all_full)
	{
		if (check_for_death(info))
			break ;
		if (experiment_ended(info))
			break ;
		all_ate(info);
		usleep(1);
	}
}
