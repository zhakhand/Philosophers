/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:43:51 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/26 17:43:06 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				l_f;
	int				r_f;
	int				meals_eaten;
	int				num_to_eat;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	long long		last_meal;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				one_dead;
	int				all_full;
	int				philo_num;
	long long		start;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	is_writing;
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
}				t_info;

t_info *init_info(char **args);
int		check_args(char **args);
char	*ft_itoa(int n);
int		ft_atoi(char const *str);
int		ft_strcmp(char const *s1, char const *s2);
long long	ft_usleep(long long ms);
long long	get_ctime(void);
void	overlord(t_info *info);
void	*routine(void *data);
void	is_doing(char *msg, t_philo *philo);
void	init_philo(t_info *info, char **args);

#endif