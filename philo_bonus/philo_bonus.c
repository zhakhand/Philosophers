#include "include/philo_bonus.h"

t_info	*init_info(char **args)
{
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(2);
	info->one_dead = 0;
	info->all_full = 0;
	info->start = 0;
	info->start = get_ctime(info);
	info->philo_num = ft_atoi(args[0]);
	return (info);
}

void    free_all(t_info *info)
{
    int     i;

    i = -1;
    while (++i < info->philo_num)
        kill(info->philos[i].pid, SIGKILL);
    sem_close(info->is_eating);
    sem_close(info->is_writing);
    sem_close(info->is_finished);
    sem_close(info->forks);
    sem_unlink("/is_eating");
    sem_unlink("/is_writing");
    sem_unlink("/is_finished");
    sem_unlink("/forks");
}

int	main(int ac, char **av)
{
	t_info	    *info;
    //pthread_t   overseer;
    int         i;

    i = -1;
	if (ac < 5 || ac > 7)
		return (0);
	if (!check_args(av + 1))
		return (0);
	info = init_info(av + 1);
	init_philo(info, av);
    sem_wait(info->is_finished);
    while (++i < info->philo_num)
    {
        info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
		{
			routine(&info->philos[i]);
			exit(0);
		}
    }
    // if (info->philo_num > 1)
    // {
    //     pthread_create(&overseer, NULL, &monitor, info);
    //     pthread_detach(overseer);
    // }
    sem_wait(info->is_finished);
    free_all(info);
	return (0);
}
