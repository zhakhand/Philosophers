/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:16:02 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 22:16:02 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i]);
	free(info->forks);
}

void	destroy_all(t_info *info)
{
	destroy_forks(info);
	pthread_mutex_destroy(&info->time_mut);
	pthread_mutex_destroy(&info->is_finished);
	pthread_mutex_destroy(&info->is_eating);
	pthread_mutex_destroy(&info->is_writing);
}
