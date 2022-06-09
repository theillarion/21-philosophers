#include "header.h"

bool	ft_think(t_environment	*env)
{
	if (env == NULL)
		return (false);
	if (env->status_death->is_die)
		return (false);
	if (ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		> env->settings->time_to_die)
	{
		ft_death(env);
		return (false);
	}
	ft_print_info(env, "is thinking", "\033[96m");
	return (true);
}

bool	ft_sleep(t_environment	*env)
{
	if (env == NULL || env->status_death->is_die)
		return (false);
	ft_print_info(env, "is sleeping", "\033[93m");
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_death(env);
	if (env->status_death->is_die)
		return (false);
	return (true);
}

bool	ft_get_forks(t_environment	*env, pthread_mutex_t	*first_fork,
			pthread_mutex_t	*second_fork)
{
	if (env == NULL || first_fork == NULL || second_fork == NULL)
		return (false);
	ft_check_result(env, pthread_mutex_lock(first_fork));
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (ft_is_died(env, first_fork, NULL))
		return (false);
	ft_check_result(env, pthread_mutex_lock(second_fork));
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (ft_is_died(env, second_fork, first_fork))
		return (false);
	return (true);
}

bool	ft_eat(t_environment	*env)
{
	if (env == NULL || env->status_death->is_die)
		return (false);
	if (ft_is_died(env, NULL, NULL))
		return (false);
	if (!ft_get_forks(env, &env->mutexes->fork[env->adrs_philo->right_fork],
			&env->mutexes->fork[env->adrs_philo->left_fork]))
		return (false);
	ft_print_info(env, "is eating", "\033[92m");
	env->adrs_philo->time_last_eat = ft_get_now_time();
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_death(env);
	ft_check_result(env, pthread_mutex_unlock(
			&env->mutexes->fork[env->adrs_philo->left_fork]));
	ft_check_result(env, pthread_mutex_unlock(
			&env->mutexes->fork[env->adrs_philo->right_fork]));
	if (env->status_death->is_die)
		return (false);
	return (true);
}

void	*ft_main_action(void	*data)
{
	t_environment	*env;

	if (data == NULL)
		return (NULL);
	env = (t_environment *)data;
	if (env->adrs_philo->id % 2 == 0)
		usleep(500);
	env->adrs_philo->time_last_eat = ft_get_now_time();
	while (env->adrs_philo->count_iteration)
	{
		if (!ft_think(env) || !ft_eat(env) || !ft_sleep(env))
			return (NULL);
		if (!env->adrs_philo->is_infinity)
			--env->adrs_philo->count_iteration;
	}
	return (NULL);
}
