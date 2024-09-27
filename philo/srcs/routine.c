/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 18:43:31 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	is_doing(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->is_writing));
	if (!philo->info->one_dead && !philo->info->all_full)
		printf("%lli %d %s\n", get_ctime(philo->info), philo->id, msg);
	pthread_mutex_unlock(&(philo->info->is_writing));
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[0]);
	is_doing("has taken a fork", philo);
	ft_usleep(philo->time_to_die, philo->info);
	is_doing("died", philo);
	pthread_mutex_unlock(&philo->info->forks[0]);
	philo->info->one_dead = 1;
}

void	eating(t_philo *philo)
{
	int	upper;
	int	lower;

	all_ate(philo->info);
	if (philo->info->all_full || philo->info->one_dead)
		return ;
	set_forks(&upper, &lower, philo);
	pthread_mutex_lock(&philo->info->forks[upper]);
	is_doing("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks[lower]);
	is_doing("has taken a fork", philo);
	philo->is_eating = 1;
	is_doing("is eating", philo);
	pthread_mutex_lock(&philo->info->is_eating);
	philo->last_meal = get_ctime(philo->info);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->is_eating);
	ft_usleep(philo->time_to_eat, philo->info);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->info->forks[upper]);
	pthread_mutex_unlock(&philo->info->forks[lower]);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->philo_num == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while ((!philo->info->one_dead && \
	get_ctime(philo->info) - philo->last_meal < \
	philo->time_to_die) || !philo->info->all_full)
	{
		eating(philo);
		if (philo->info->one_dead)
			break ;
		is_doing("is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo->info);
		is_doing("is thinking", philo);
	}
	return (NULL);
}
