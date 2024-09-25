/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:30 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/25 16:23:31 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_forks(pthread_mutex_t **forks, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_mutex_init(forks[i], NULL);
}

void	apply_args(t_philo *philo, char **args, t_info *info)
{
	philo->time_to_die = ft_atoi(args[0]);
	philo->time_to_eat = ft_atoi(args[1]);
	philo->time_to_sleep = ft_atoi(args[2]);
	if (args[3])
		philo->num_to_eat = ft_atoi(args[3]);
	else
		philo->num_to_eat = -1;
	philo->eating = 0;
	philo->died = 0;
	philo->meals_eaten = 0;
	philo->is_last = 0;
	philo->start_time = get_ctime();
	philo->last_meal = get_ctime();
	philo->writing = &info->writing;
	philo->dead = &info->dead;
	philo->eats = &info->eats;
}

t_philo	*init_philo(t_info *info, char **args, pthread_mutex_t **forks)
{
	t_philo *philos;
	int		i;
	
	i = -1;
	philos = (t_philo*)malloc(sizeof(t_philo) * info->philo_num);
	*forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!philos || !*forks)
		return (NULL);
	init_forks(forks, info->philo_num);
	while (++i < info->philo_num)
	{
		philos[i].id = i + 1;
		apply_args(&philos[i], args, info);
		if (i == info->philo_num - 1)
			philos[i].is_last = 1;
		philos[i].l_fork = forks[i];
		if (i == 0)
			philos[i].r_fork = forks[info->philo_num - 1];
		else
			philos[i].r_fork = forks[i - 1];
	}
	return philos;
}
