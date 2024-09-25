/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/25 16:16:43 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->writing);
	time = get_ctime() - philo->start_time;
	if (philo->died != 0)
		printf("%d %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->writing);
}

void	sleeping(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->writing);
	time = get_ctime() - philo->start_time;
	if (philo->died != 0)
		printf("%d %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(philo->writing);
}

void	took_fork_eating(char *msg, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->writing);
	time = get_ctime() - philo->start_time;
	if (philo->died != 0)
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->writing);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	took_fork_eating("took a fork", philo);
	if (philo->is_last)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	took_fork_eating("took a fork", philo);
	philo->eating = 1;
	took_fork_eating("is eating", philo);
	pthread_mutex_lock(philo->eats);
	philo->last_meal = get_ctime();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eats);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo*)data;
	while (check_if_died(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (data);
}