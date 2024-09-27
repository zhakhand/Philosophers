/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:50:55 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 18:38:08 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_info	*init_info(char **args)
{
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(2);
	info->one_dead = 0;
	info->all_full = 0;
	info->start = 0;
	info->start = get_ctime(info);
	info->philo_num = ft_atoi(args[0]);
	return (info);
}

void	join_threads(t_info *info)
{
	int			i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, \
		NULL, &routine, &info->philos[i]))
			return (destroy_all(info));
	}
	if (info->philo_num > 1)
		overlord(info);
	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_join(info->philos[i].thread, NULL))
			return (destroy_all(info));
	}
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac < 5 || ac > 7)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(av + 1);
	init_philo(info, av);
	join_threads(info);
	destroy_all(info);
	free(info);
	return (0);
}
