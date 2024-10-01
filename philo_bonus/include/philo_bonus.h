#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				l_f;
	int				r_f;
	int				is_eating;
	int				is_full;
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
	sem_t			*is_eating;
	sem_t			*is_writing;
	sem_t			*is_finished;
	sem_t			*dead_full;
	sem_t			*is_full;
	sem_t			*forks;
	t_philo			philos[200];
}				t_info;

/*INITIALIZE*/
t_info		*init_info(char **args);
void		init_philo(t_info *info, char **args);
/*TIMESTAMP*/
long long	get_ctime(t_info *info);
long long	ft_usleep(long long ms, t_info *info);
/*ROUTINE*/
void		routine(t_philo *philo);
void		is_doing(char *msg, t_philo *philo);
/*OVERSEER*/
void		overlord(t_info *info);
void		*send_signal(void *data);
void		*monitor(void *data);
void		all_ate(t_info *info);
int			exp_ended(t_info *info);
/*UTILS*/
char		*ft_itoa(int n);
int			ft_atoi(char const *str);
char		*ft_strjoin(char *s1, char *s2);
int			check_args(char **args);
int			ft_strcmp(char const *s1, char const *s2);
void		set_forks(int *upper, int *lower, t_philo *philo);
/*CLEANUP*/

#endif