/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:24 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 16:44:54 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	valid_arg(char *s)
{
	char	*num;

	if (ft_atoi(s) < 0)
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