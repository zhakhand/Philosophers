/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:30 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 18:42:53 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
		{
			while (--i)
				pthread_mutex_destroy(&info->forks[i]);
			exit(1);
		}
	}
	if (pthread_mutex_init(&(info->is_eating), NULL))
	{
		destroy_forks(info);
		exit(1);
	}
	if (pthread_mutex_init(&(info->is_writing), NULL))
	{
		pthread_mutex_destroy(&info->is_eating);
		destroy_forks(info);
		exit(1);
	}
}

void	apply_args(t_philo *philo, char **args)
{
	philo->time_to_die = ft_atoi(args[2]);
	philo->time_to_eat = ft_atoi(args[3]);
	philo->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		philo->num_to_eat = ft_atoi(args[5]);
	else
		philo->num_to_eat = -1;
	philo->meals_eaten = 0;
	philo->last_meal = philo->info->start;
	philo->is_eating = 0;
}

void	init_philo(t_info *info, char **args)
{
	int		i;

	i = -1;
	init_mutexes(info);
	while (++i < info->philo_num)
	{
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		apply_args(&info->philos[i], args);
		info->philos[i].l_f = i;
		info->philos[i].r_f = (i + 1) % info->philo_num;
	}
}
