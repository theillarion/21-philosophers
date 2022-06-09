#include "header.h"

#ifdef DEBUG_MODE

void	ft_print_info(t_environment	*env, const char	*event,
	const char	*color)
{
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->print));
	printf("%s[%llu] #%u %s\033[0m\n", color,
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->adrs_philo->id, event);
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->print));
}

void	ft_print_died(t_environment	*env)
{
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->print));
	printf("%s[%llu] #%u %s\033[0m\n", "\033[91m",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->status_death->id, "died");
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->print));
}

#else

void	ft_print_info(t_environment	*env, const char	*event,
	const char	*color)
{
	(void)color;
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->print));
	printf("%llu %u %s\n",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->adrs_philo->id, event);
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->print));
}

void	ft_print_died(t_environment	*env)
{
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->print));
	printf("%llu %u %s\n",
		ft_get_difference_time_now_ms(&env->settings->start_time),
		env->status_death->id, "died");
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->print));
}

#endif
