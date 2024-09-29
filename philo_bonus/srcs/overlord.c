#include "../include/philo_bonus.h"

int	exp_ended(t_info *info)
{
	int	end;

	end = (info->all_full || info->one_dead);
    return (end);
}

void	all_ate(t_info *info)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
    sem_wait(info->is_eating);
	while (info->philos[i].num_to_eat != -1 && i < info->philo_num)
	{
		if (info->philos[i].meals_eaten >= info->philos[i].num_to_eat)
			count++;
		i++;
	}
    sem_post(info->is_eating);
	if (count == info->philo_num)
	{
		info->all_full = 1;
	}
}

void    *monitor(void *data)
{
    t_info  *info;
    int     i;

    info = (t_info *)data;
    while(!exp_ended(info))
    {
        i = -1;
        while(++i < info->philo_num && !info->one_dead)
        {
            sem_wait(info->is_eating);
            if (get_ctime(info) - info->philos[i].last_meal > \
            info->philos[i].time_to_die && !info->philos[i].is_eating)
            {
                is_doing("died", &info->philos[i]);
                info->one_dead = 1;
                sem_post(info->is_eating);
                break ;
            }
            sem_post(info->is_eating);
        }
        if (exp_ended(info))
        {
            sem_post(info->is_finished);
            break ;
        }
        all_ate(info);
    }
    return (NULL);
}