/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:19 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/02 13:14:29 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		kill(info->philos[i].pid, SIGKILL);
	sem_close(info->orders);
	sem_close(info->is_eating);
	sem_close(info->is_writing);
	sem_close(info->is_finished);
	sem_close(info->forks);
	sem_close(info->dead);
	if (info->meal_goal != -1)
		sem_close(info->is_full);
	if (info->philos)
		free(info->philos);
}

void	run_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			routine(&info->philos[i]);
	}
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(av + 1);
	init_philo(&info, av);
	if (!info.philos)
		return (free_all(&info), 0);
	sem_wait(info.is_finished);
	run_philos(&info);
	if (info.philo_num > 1 && info.meal_goal != -1)
		monitor(&info);
	sem_wait(info.is_finished);
	free_all(&info);
	return (0);
}
