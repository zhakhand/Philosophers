/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:50:55 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:28:58 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	join_threads(t_info *info)
{
	int			i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, \
		NULL, &routine, &info->philos[i]))
			return ;
	}
	if (info->philo_num > 1)
		overlord(info);
	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_join(info->philos[i].thread, NULL))
			return ;
	}
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(av + 1);
	if (!info)
		return (1);
	if (!init_philo(info, av))
		return (1);
	join_threads(info);
	destroy_all(info);
	free(info->philos);
	free(info);
	return (0);
}
