/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:30 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:32:18 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_other(t_info *info)
{
	if (pthread_mutex_init(&(info->is_eating), NULL))
	{
		destroy_forks(info);
		pthread_mutex_destroy(&info->time_mut);
		return (free(info), 0);
	}
	if (pthread_mutex_init(&(info->is_writing), NULL))
	{
		pthread_mutex_destroy(&info->is_eating);
		destroy_forks(info);
		pthread_mutex_destroy(&info->time_mut);
		return (free(info), 0);
	}
	if (pthread_mutex_init(&(info->is_finished), NULL))
	{
		pthread_mutex_destroy(&info->is_eating);
		pthread_mutex_destroy(&info->is_writing);
		destroy_forks(info);
		pthread_mutex_destroy(&info->time_mut);
		return (free(info), 0);
	}
	return (1);
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* (info->philo_num + 1));
	if (!info->forks)
		return (free(info), 0);
	while (++i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
		{
			while (--i)
				pthread_mutex_destroy(&info->forks[i]);
			free(info);
			return (0);
		}
	}
	return (init_other(info));
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

int	init_philo(t_info *info, char **args)
{
	int		i;

	i = -1;
	if (!init_mutexes(info))
		return (0);
	info->philos = (t_philo *)malloc(sizeof(t_philo) * (info->philo_num + 1));
	if (!info->philos)
		return (destroy_all(info), free(info), 0);
	while (++i < info->philo_num)
	{
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		apply_args(&info->philos[i], args);
		info->philos[i].l_f = i;
		info->philos[i].r_f = (i + 1) % info->philo_num;
	}
	return (1);
}

t_info	*init_info(char **args)
{
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (pthread_mutex_init(&info->time_mut, NULL))
		return (free(info), NULL);
	info->one_dead = 0;
	info->all_full = 0;
	info->start = 0;
	info->start = get_ctime(info);
	info->philo_num = ft_atoi(args[0]);
	info->to_eat = -1;
	if (args[4])
		info->to_eat = ft_atoi(args[4]);
	return (info);
}
