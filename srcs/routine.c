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
	if (!philo->info->one_dead)
		printf("%lli %d %s\n", (get_ctime() - philo->info->start), philo->id, msg);
	pthread_mutex_unlock(&(philo->info->is_writing));
}

void	eating(t_philo *philo)
{
	int	upper;
	int	lower;

	upper = philo->l_f;
	lower = philo->r_f;
	if (philo->id % 2)
	{
		upper = philo->r_f;
		lower = philo->l_f;
	}
	pthread_mutex_lock(&philo->info->forks[upper]);
	is_doing("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks[lower]);
	is_doing("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->is_eating);
	is_doing("is eating", philo);
	philo->last_meal = get_ctime();
	pthread_mutex_unlock(&philo->info->is_eating);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->forks[upper]);
	pthread_mutex_unlock(&philo->info->forks[lower]);
}

void	one_phil(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_f]);
	is_doing("has taken a fork", philo);
	ft_usleep(philo->time_to_die);
	is_doing("died", philo);
	philo->info->one_dead = 1;
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	if (philo->info->philo_num == 1)
	{
		one_phil(philo);
		return NULL;
	}
	while (!philo->info->one_dead)
	{
		eating(philo);
		if (philo->info->one_dead)
			break ;
		if (philo->num_to_eat != -1 && philo->info->all_full)
			break ;
		if (philo->num_to_eat != -1 && philo->meals_eaten >= philo->num_to_eat)
			break ;
		is_doing("is sleeping", philo);
		ft_usleep(philo->time_to_sleep);
		is_doing("is thinking", philo);
	}
	return (NULL);
}