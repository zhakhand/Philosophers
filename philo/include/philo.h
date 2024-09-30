/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:43:51 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/09/30 18:18:01 by dzhakhan         ###   ########.fr       */
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
	int				left_fork;
	int				right_fork;
	int				is_eating;
	int				meals_eaten;
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
	int				meal_goal;
	long long		start;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	is_writing;
	pthread_mutex_t	is_finished;
	pthread_mutex_t	time_mut;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_info;

/*INITIALIZE*/
t_info		*init_info(char **args);
int			init_philo(t_info *info, char **args);
/*TIMESTAMP*/
long long	get_ctime(t_info *info);
long long	ft_usleep(long long milliseconds, t_info *info);
/*ROUTINE*/
void		*routine(void *data);
void		is_doing(char *msg, t_philo *philo);
/*OVERSEER*/
void		overseer(t_info *info);
int			experiment_ended(t_info *info);
/*UTILS*/
char		*ft_itoa(int n);
int			ft_atoi(char const *str);
int			check_args(char **args);
int			ft_strcmp(char const *s1, char const *s2);
void		set_forks(int *first, int *second, t_philo *philo);
/*CLEANUP*/
void		destroy_forks(t_info *info);
void		destroy_all(t_info *info);

#endif