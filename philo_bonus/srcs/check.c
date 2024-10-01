/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:53:10 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/10/01 08:53:11 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	valid_arg(char *s)
{
	char	*num;

	if (ft_atoi(s) <= 0)
		return (0);
	num = ft_itoa(ft_atoi(s));
	if (!num)
		return (free(num), 0);
	if (ft_strcmp(num, s))
		return (free(num), 0);
	free(num);
	return (1);
}

int	check_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (!valid_arg(args[i]))
			return (0);
	}
	if (ft_atoi(args[0]) <= 0)
		return (0);
	return (1);
}

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
