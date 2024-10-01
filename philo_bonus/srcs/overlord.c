/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:16 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/01 09:33:59 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	experiment_ended(t_info *info)
{
	int	end;

	sem_wait(info->dead_full);
	end = (info->all_full == info->philo_num || info->one_dead);
	sem_post(info->dead_full);
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
			return (sem_post(philo->info->dead_full), \
			sem_post(philo->info->is_eating), \
			sem_post(philo->info->is_finished), 1);
	}
	return (0);
}

int	check_for_death(t_philo *philo)
{
	sem_wait(philo->info->dead_full);
	if (get_ctime(philo->info) - philo->last_meal >= philo->time_to_die \
	&& !philo->is_eating && !philo->info->one_dead)
	{
		is_doing("died", philo);
		philo->info->one_dead = 1;
		return (sem_post(philo->info->dead_full), \
		sem_post(philo->info->is_eating), \
		sem_post(philo->info->is_finished), 1);
	}
	sem_post(philo->info->dead_full);
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
		sem_post(philo->info->dead_full);
		usleep(1);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *)data;
	while (1)
	{
		usleep(1);
		sem_wait(info->is_full);
		i++;
		if (i == info->philo_num)
		{
			sem_post(info->is_finished);
			break ;
		}
	}
	return (NULL);
}
