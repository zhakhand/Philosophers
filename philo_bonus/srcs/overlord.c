/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:16 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/02 12:58:17 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	experiment_ended(t_info *info)
{
	int	end;

	sem_wait(info->dead);
	end = (info->all_full == info->philo_num || info->one_dead);
	sem_post(info->dead);
	return (end);
}

int	check_if_full(t_philo *philo)
{
	if (philo->num_to_eat != -1 && philo->meals_eaten >= philo->num_to_eat)
	{
		if (!philo->is_full)
		{
			philo->is_full = 1;
			philo->info->all_full++;
			sem_post(philo->info->is_full);
		}
		if (philo->info->all_full == philo->info->philo_num)
			return (sem_post(philo->info->dead), \
			sem_post(philo->info->is_eating), \
			sem_post(philo->info->is_finished), 1);
	}
	return (0);
}

int	check_for_death(t_philo *philo)
{
	int	i;

	sem_wait(philo->info->dead);
	usleep(1);
	if (get_ctime(philo->info) - philo->last_meal >= philo->time_to_die \
	&& !philo->is_eating && !philo->info->one_dead)
	{
		is_doing("died", philo);
		philo->info->one_dead = 1;
		if (philo->num_to_eat != -1)
		{
			i = -1;
			while (++i < philo->info->philo_num)
				sem_post(philo->info->is_full);
		}
		return (sem_post(philo->info->dead), \
		sem_post(philo->info->is_eating), \
		sem_post(philo->info->is_finished), 1);
	}
	sem_post(philo->info->dead);
	return (0);
}

void	*send_signal(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->info->is_eating);
		if (check_for_death(philo))
			break ;
		if (check_if_full(philo))
			break ;
		sem_post(philo->info->is_eating);
		sem_post(philo->info->dead);
		usleep(1);
	}
	return (NULL);
}

void	monitor(t_info *info)
{
	int		i;

	i = 0;
	while (!info->one_dead)
	{
		sem_wait(info->is_full);
		i++;
		if (i == info->philo_num)
		{
			sem_post(info->is_full);
			sem_post(info->is_finished);
			break ;
		}
		usleep(1);
	}
	return ;
}
