/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:50:55 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/24 13:01:13 by dzhakhan         ###   ########.fr       */
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
	
}

int	main(int ac, char **av)
{
	t_info *info;
	
	if (ac < 5 || ac > 7)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(ac - 1, av + 1);
}