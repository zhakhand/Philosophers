/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:43:51 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/25 16:23:03 by dzhakhan         ###   ########.fr       */
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
	int				eating;
	int				meals_eaten;
	int				start_time;
	int				last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	int				*died;
	int				is_last;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eats;
}				t_philo;

typedef struct s_info
{
	int				is_dead;
	int				philo_num;
	pthread_mutex_t	dead;
	pthread_mutex_t	eats;
	pthread_mutex_t	writing;
	t_philo			*philos;
}				t_info;

t_info *init_info(int sz, char **args);
int		check_args(char **args);
char	*ft_itoa(int n);
int		ft_atoi(char const *str);
int		ft_strcmp(char const *s1, char const *s2);
int	ft_usleep(int ms);
int	get_ctime(void);
void	observe(void *data);
void	*routine(void *data);
int	check_if_died(t_philo *philo);
t_philo	*init_philo(t_info *info, char **args, pthread_mutex_t **forks);

#endif