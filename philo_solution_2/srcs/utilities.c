#include "header.h"

void	ft_smart_free(void	**memory)
{
	if (memory != NULL && *memory != NULL)
	{
		free(*memory);
		*memory = NULL;
	}
}

bool	ft_smart_sleep(t_environment	*env, size_t sleep_milliseconds)
{
	t_time	start;
	t_time	current;

	if (env == NULL)
		return (false);
	start = ft_get_now_time();
	current = ft_copy_time(&start);
	while (!env->status_death->is_die
		&& ft_get_difference_time_ms(&start, &current)
		< sleep_milliseconds)
	{
		if (ft_get_difference_time_ms(&env->adrs_philo->time_last_eat, &current)
			>= env->settings->time_to_die)
			return (false);
		usleep(100);
		current = ft_get_now_time();
	}
	return (true);
}
