/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:47:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 16:26:20 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	is_doing(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->is_writing));
	if (!experiment_ended(philo->info))
		printf("%lli %d %s\n", get_ctime(philo->info), philo->id, msg);
	pthread_mutex_unlock(&(philo->info->is_writing));
}

/********************************************************/
/* Even numbered philosophers take the left fork first  */
/*    while odd ones take the right fork.               */
/*		this ensures synchronisation                    */
/********************************************************/
void	eating(t_philo *philo)
{
	int	first;
	int	second;

	set_forks(&first, &second, philo);
	pthread_mutex_lock(&philo->info->forks[first]);
	is_doing("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks[second]);
	is_doing("has taken a fork", philo);
	pthread_mutex_lock(&philo->info->is_eating);
	philo->is_eating = 1;
	is_doing("is eating", philo);
	philo->last_meal = get_ctime(philo->info);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->is_eating);
	ft_usleep(philo->time_to_eat, philo->info);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->info->forks[first]);
	pthread_mutex_unlock(&philo->info->forks[second]);
}

/***********************************************/
/* different behaviour for a single philosopher*/
/***********************************************/
void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[0]);
	is_doing("has taken a fork", philo);
	ft_usleep(philo->time_to_die, philo->info);
	is_doing("died", philo);
	pthread_mutex_unlock(&philo->info->forks[0]);
	philo->info->one_dead = 1;
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
	while (!experiment_ended(philo->info))
	{
		is_doing("is thinking", philo);
		eating(philo);
		if (experiment_ended(philo->info))
			break ;
		is_doing("is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo->info);
		is_doing("is thinking", philo);
	}
	return (NULL);
}
