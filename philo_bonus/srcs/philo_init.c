#include "../include/philo_bonus.h"

void	init_mutexes(t_info *info)
{
	sem_unlink("/is_eating");
	sem_unlink("/is_writing");
	sem_unlink("/is_finished");
	sem_unlink("/forks");
	sem_unlink("/dead_full");
	info->is_eating = sem_open("/is_eating", O_CREAT | O_EXCL, 0644, 1);
	info->is_writing = sem_open("/is_writing", O_CREAT | O_EXCL, 0644, 1);
	info->is_finished = sem_open("/is_finished", O_CREAT | O_EXCL, 0644, 1);
	info->dead_full = sem_open("/dead_full", O_CREAT | O_EXCL, 0644, 1);
	info->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, info->philo_num);
}

void	apply_args(t_philo *philo, char **args)
{
	philo->time_to_die = ft_atoi(args[2]);
	philo->time_to_eat = ft_atoi(args[3]);
	philo->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		philo->num_to_eat = ft_atoi(args[5]);
	else
		philo->num_to_eat = -1;
	philo->meals_eaten = 0;
	philo->last_meal = philo->info->start;
	philo->is_eating = 0;
	philo->is_full = 0;
}

void	init_philo(t_info *info, char **args)
{
	int		i;

	i = -1;
	init_mutexes(info);
	while (++i < info->philo_num)
	{
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		apply_args(&info->philos[i], args);
		info->philos[i].l_f = i;
		info->philos[i].r_f = (i + 1) % info->philo_num;
	}
}
