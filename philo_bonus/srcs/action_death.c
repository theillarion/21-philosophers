#include <header.h>

void	ft_death(t_environment	*env)
{
	exit(env->adrs_philo->id + 1);
}

bool	ft_is_died(t_environment	*env, sem_t	*semaphore1,
			sem_t	*semaphore2)
{
	if (env == NULL
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (semaphore1 != NULL)
			sem_post(semaphore1);
		if (semaphore2 != NULL)
			sem_post(semaphore2);
		return (true);
	}
	return (false);
}
