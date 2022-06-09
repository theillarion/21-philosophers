#include <header.h>

bool	ft_death(t_environment	*env)
{
	if (env == NULL)
		return (false);
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->death));
	if (env->status_death->is_die)
	{
		ft_check_result(env, pthread_mutex_unlock(&env->mutexes->death));
		return (false);
	}
	env->status_death->is_die = true;
	env->status_death->id = env->adrs_philo->id;
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->death));
	return (false);
}

bool	ft_is_died(t_environment	*env, pthread_mutex_t	*mutex1,
			pthread_mutex_t	*mutex2)
{
	if (env == NULL)
		return (true);
	if (env->status_death->is_die
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (!env->status_death->is_die)
			ft_death(env);
		if (mutex1 != NULL)
			ft_check_result(env, pthread_mutex_unlock(mutex1));
		if (mutex2 != NULL)
			ft_check_result(env, pthread_mutex_unlock(mutex2));
		return (true);
	}
	return (false);
}
