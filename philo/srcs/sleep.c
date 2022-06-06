#include "header.h"

bool	ft_smart_sleep(t_main	*env, const t_time	*time_last_eat,
	size_t sleep_milliseconds)
{
	t_time	start;
	t_time	current;

	if (env == NULL)
		return (false);
	start = ft_get_now_time();
	current = ft_copy_time(&start);
	while (!env->status->is_die && ft_get_difference_time_ms(&start, &current) < sleep_milliseconds)
	{
		if (ft_get_difference_time_ms(time_last_eat, &current) >= env->settings->time_to_die)
			return (false);
		usleep(100);
		current = ft_get_now_time();
	}
	return (true);
}
