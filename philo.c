/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:50:55 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 16:57:04 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_info	*init_info(char **args)
{
	t_info	*info;
	t_philo philo;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(0);
	info->one_dead = 0;
	info->all_full = 0;
	info->start = get_ctime();
	info->philo_num = ft_atoi(args[0]);
	return info;
}

void	join_threads(t_info *info)
{
	int			i;
	
	i = -1;
	info->start = get_ctime();
	while (++i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, NULL, &routine, &info->philos[i]))
			exit (2);
		info->philos[i].last_meal = get_ctime();
	}
	overlord(info);
	i = -1;
	while (++i < info->philo_num)
		pthread_join(info->philos[i].thread, NULL);
	pthread_mutex_destroy(&info->is_writing);
	pthread_mutex_destroy(&info->is_eating);
	i = -1;
	while (++i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i]);
}

int	main(int ac, char **av)
{
	t_info			*info;
	
	if (ac < 5 || ac > 7)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(av + 1);
	init_philo(info, av);
	join_threads(info);
	free(info);
	return 0;
}