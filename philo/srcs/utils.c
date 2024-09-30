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

void	set_forks(int *first, int *second, t_philo *philo)
{
	*first = philo->left_fork;
	*second = philo->right_fork;
	if (philo->id % 2)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
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

int	ft_atoi(char const *str)
{
	int		result;
	int		sign;
	long	last;

	result = 0;
	sign = 1;
	last = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		if (last != (last * 10 + *str - '0') / 10)
			return ((sign >= 0) * -1);
		last = last * 10 + *str - '0';
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

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
