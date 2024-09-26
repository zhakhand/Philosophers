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
	int				is_eating;
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

/*INITIALIZE*/
t_info		*init_info(char **args);
void		init_philo(t_info *info, char **args);
/*TIMESTAMP*/
long long	get_ctime(t_info *info);
long long	ft_usleep(long long ms, t_info *info);
/*ROUTINE*/
void		*routine(void *data);
void		is_doing(char *msg, t_philo *philo);
/*OVERSEER*/
void		overlord(t_info *info);
void		all_ate(t_info *info);
/*UTILS*/
char		*ft_itoa(int n);
int			ft_atoi(char const *str);
int			check_args(char **args);
int			ft_strcmp(char const *s1, char const *s2);
void		set_forks(int *upper, int *lower, t_philo *philo);
/*CLEANUP*/
void		destroy_forks(t_info *info);
void		destroy_all(t_info *info);

#endif