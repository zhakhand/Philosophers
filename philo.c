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

void	init_info(t_info *info, int sz, char **args)
{
	if (!check_args(args))
		exit(3);
	info->is_dead = 0;
}

int	main(int ac, char **av)
{
	t_info *info;
	
	info = malloc(sizeof(t_info));
	if (!info)
		return (2);
	if (ac == 5 || ac == 6)
		init_info(info, ac - 1, av + 1);
}