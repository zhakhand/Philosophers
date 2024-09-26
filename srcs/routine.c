/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 17:12:05 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	is_doing(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->is_writing));
	if (!philo->info->one_dead)
		printf("%li %d %s\n", get_ctime() - philo->info->start, philo->id, msg);
	pthread_mutex_unlock(&(philo->info->is_writing));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_f]);
	is_doing("took a fork", philo);
	pthread_mutex_lock(&philo->info->forks[philo->r_f]);
	is_doing("took a fork", philo);
	pthread_mutex_lock(&philo->info->is_eating);
	is_doing("is eating", philo);
	philo->last_meal = get_ctime();
	pthread_mutex_unlock(&philo->info->is_eating);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->forks[philo->l_f]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_f]);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	if (philo->id % 2)
		ft_usleep(philo->time_to_eat);
	while (!philo->info->one_dead)
	{
		eating(philo);
		if (philo->num_to_eat != -1 && philo->info->all_full)
			break ;
		if (philo->info->one_dead)
			break ;
		is_doing("is sleeping\n", philo);
		ft_usleep(philo->time_to_sleep);
		is_doing("is thinking\n", philo);
	}
	return (NULL);
}