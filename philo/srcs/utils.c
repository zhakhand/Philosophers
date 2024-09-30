/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:32 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:28:27 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_forks(int *upper, int *lower, t_philo *philo)
{
	*upper = philo->l_f;
	*lower = philo->r_f;
	if (philo->id % 2)
	{
		*upper = philo->r_f;
		*lower = philo->l_f;
	}
}

int	ft_strcmp(char const *s1, char const *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

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
