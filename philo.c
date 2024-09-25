/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:50:55 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/25 16:25:08 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_info	*init_info(int sz, char **args)
{
	t_info	*info;
	t_philo philo;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(0);
	info->philos = NULL;
	info->is_dead = 0;
	info->philo_num = ft_atoi(args[0]);
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->eats, NULL);
	pthread_mutex_init(&info->writing, NULL);
	return info;
}

void	join_threads(t_info *info, pthread_mutex_t *forks)
{
	int			i;
	// pthread_t	overlord;
	
	// i = -1;
	// if (pthread_create(&overlord, NULL, &observe, info->philos))
	// 	exit (2);
	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, NULL, &routine, &info->philos[i]))
			exit (2);
	}
	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_join(info->philos[i].thread, NULL))
			exit (2);
	}
}

int	main(int ac, char **av)
{
	t_info			*info;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	
	if (ac < 5 || ac > 7)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(ac - 1, av + 1);
	forks = NULL;
	philos = init_philo(info, av + 2, &forks);
	if (!philos)
		return (free(info), 2);
	info->philos = philos;
	join_threads(info, forks);
	return 0;
}