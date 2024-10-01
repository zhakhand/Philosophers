/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:25 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/01 09:03:41 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

/*EACH PHILOSPHERS SENDS A SIGNAL WHEN THEY DIE OR FULL*/

void	is_doing(char *msg, t_philo *philo)
{
	sem_wait((philo->info->is_writing));
	if (!exp_ended(philo->info))
		printf("%lli %d %s\n", get_ctime(philo->info), philo->id, msg);
	sem_post((philo->info->is_writing));
}

void	one_philo(t_philo *philo)
{
	sem_wait(philo->info->forks);
	is_doing("has taken a fork", philo);
	ft_usleep(philo->time_to_die, philo->info);
	is_doing("died", philo);
	sem_post(philo->info->forks);
	philo->info->one_dead = 1;
	sem_post(philo->info->is_finished);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->info->forks);
	is_doing("has taken a fork", philo);
	sem_wait(philo->info->forks);
	is_doing("has taken a fork", philo);
	sem_wait(philo->info->is_eating);
	philo->is_eating = 1;
	is_doing("is eating", philo);
	philo->last_meal = get_ctime(philo->info);
	philo->meals_eaten++;
	sem_post(philo->info->is_eating);
	ft_usleep(philo->time_to_eat, philo->info);
	philo->is_eating = 0;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	routine(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->info->philo_num == 1)
	{
		one_philo(philo);
		return ;
	}
	pthread_create(&monitor, NULL, &send_signal, philo);
	pthread_detach(monitor);
	while (!exp_ended(philo->info))
	{
		is_doing("is thinking", philo);
		eating(philo);
		if (exp_ended(philo->info))
		{
			sem_post(philo->info->is_finished);
			break ;
		}
		is_doing("is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo->info);
		is_doing("is thinking", philo);
		usleep(1);
	}
}
