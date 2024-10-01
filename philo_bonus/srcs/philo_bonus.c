/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:19 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/01 09:40:11 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		kill(info->philos[i].pid, SIGKILL);
	sem_close(info->is_eating);
	sem_close(info->is_writing);
	sem_close(info->is_finished);
	sem_close(info->forks);
	sem_close(info->dead_full);
	sem_close(info->is_full);
	sem_unlink("/is_eating");
	sem_unlink("/is_writing");
	sem_unlink("/is_finished");
	sem_unlink("/forks");
	sem_unlink("/dead_full");
	sem_unlink("/is_full");
	if (info->philos)
		free(info->philos);
}

int	overseer(t_info *info)
{
	pthread_t	overseer;

	if (info->philo_num > 1)
	{
		if (pthread_create(&overseer, NULL, &monitor, info))
			return (sem_post(info->is_finished));
		if (pthread_detach(overseer))
			return (sem_post(info->is_finished));
	}
	sem_wait(info->is_finished);
	free_all(info);
	return (0);
}

void	run_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
		{
			routine(&info->philos[i]);
			exit(0);
		}
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
	overseer(&info);
	return (0);
}
