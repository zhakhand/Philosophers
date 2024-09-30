#include "../include/philo_bonus.h"

int	exp_ended(t_info *info)
{
	int	end;

	sem_wait(info->dead_full);
	end = (info->all_full == 5 || info->one_dead);
	sem_post(info->dead_full);
    return (end);
}

void	*send_signal(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->info->dead_full);
		sem_wait(philo->info->is_eating);
		if (get_ctime(philo->info) - philo->last_meal >= philo->time_to_die && !philo->is_eating)
		{
			is_doing("died", philo);
			philo->info->one_dead = 1;
			return (sem_post(philo->info->dead_full), sem_post(philo->info->is_eating), sem_post(philo->info->is_finished), NULL);
		}
		if (philo->meals_eaten != -1 && philo->meals_eaten >= philo->num_to_eat)
		{
			if (!philo->is_full)
			{
				philo->is_full = 1;
				philo->info->all_full++;
			}
			if (philo->info->all_full == 5)
				return (sem_post(philo->info->dead_full), sem_post(philo->info->is_eating), sem_post(philo->info->is_finished), NULL);
		}
		sem_post(philo->info->is_eating);
		sem_post(philo->info->dead_full);
		usleep(1000);
	}
	return (NULL);
}

void    *monitor(void *data)
{
    t_info  *info;

    info = (t_info *)data;
    while(!exp_ended(info))
    { 
    	sem_wait(info->is_finished);
    }
	sem_post(info->is_finished);
    return (NULL);
}