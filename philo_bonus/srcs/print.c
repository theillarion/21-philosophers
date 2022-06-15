#include "header.h"

#ifdef DEBUG_MODE

void	ft_print_info(t_environment	*env, const char	*event,
	const char	*color)
{
	sem_wait(env->semaphores->print);
	printf("%s[%llu] #%u %s\033[0m\n", color,
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->adrs_philo->id, event);
	sem_post(env->semaphores->print);
}

void	ft_print_died(t_environment	*env, short id)
{
	printf("%s[%llu] #%u %s\033[0m\n", "\033[91m",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		id, "died");
}

#else

void	ft_print_info(t_environment	*env, const char	*event,
	const char	*color)
{
	(void)color;
	sem_wait(env->semaphores->print);
	printf("%llu %u %s\n",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->adrs_philo->id, event);
	sem_post(env->semaphores->print);
}

void	ft_print_died(t_environment	*env, short id)
{
	printf("%llu %u %s\n",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		id, "died");
}

#endif
