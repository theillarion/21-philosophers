#include "header.h"

void	ft_die(t_main	*env)
{
	if (env == NULL)
		return;
	check(pthread_mutex_lock(&env->mutexes->death));
	if (env->status->is_die)
	{
		check(pthread_mutex_unlock(&env->mutexes->death));
		return;
	}
	env->status->is_die = true;
	env->status->id = env->adrs_philo->id;
	check(pthread_mutex_unlock(&env->mutexes->death));
}

bool	ft_think(t_main	*arg)
{
	if (arg == NULL)
		return (false);
	if (arg->status->is_die)
		return (false);
	if (ft_get_difference_time_now_ms(&arg->adrs_philo->time_last_eat)
		> arg->settings->time_to_die)
	{
		ft_die(arg);
		return (false);
	}
	ft_print_info(arg, "is thinking", "\033[96m");
	return (true);
}

bool	ft_get_fork(t_main	*env, bool is_right_fork)
{
	if (env == NULL)
		return (false);
	if (is_right_fork)
		check(pthread_mutex_lock(
			&env->mutexes->fork[env->adrs_philo->right_fork]));
	else
		check(pthread_mutex_lock(
			&env->mutexes->fork[env->adrs_philo->left_fork]));
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (env->status->is_die || ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (!env->status->is_die)
			ft_die(env);
		if (!is_right_fork)
			check(pthread_mutex_unlock(
				&env->mutexes->fork[env->adrs_philo->left_fork]));
		check(pthread_mutex_unlock(
			&env->mutexes->fork[env->adrs_philo->right_fork]));
		check(pthread_mutex_unlock(&env->mutexes->all_forks));
		check(pthread_mutex_unlock(&env->mutexes->queue));
		return (false);
	}
	return (true);
}

bool	ft_get_forks(t_main	*env)
{
	if (env == NULL || env->status->is_die
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (!env->status->is_die)
			ft_die(env);
		check(pthread_mutex_unlock(&env->mutexes->queue));
		return (false);
	}
	check(pthread_mutex_lock(&env->mutexes->all_forks));
	if (!ft_get_fork(env, true))
		return (false);
	if (!ft_get_fork(env, false))
		return (false);
	check(pthread_mutex_unlock(&env->mutexes->all_forks));
	ft_my_push(&env->queue, env->adrs_philo->id);
	check(pthread_mutex_unlock(&env->mutexes->queue));
	ft_print_info(env, "is eating", "\033[92m");
	env->adrs_philo->time_last_eat = ft_get_now_time();
	bool flag = ft_smart_sleep(env, env->settings->time_to_eat);
	check(pthread_mutex_unlock(
		&env->mutexes->fork[env->adrs_philo->left_fork]));
	check(pthread_mutex_unlock(
		&env->mutexes->fork[env->adrs_philo->right_fork]));
	if (!flag)
		ft_die(env);
	if (env->status->is_die)
		return (false);
	return (true);
}

bool	ft_is_died(t_main	*env)
{
	if (env == NULL)
		return (true);
	if (env->status->is_die
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
		return (true);
	return (false);
}

bool	ft_eat(t_main	*arg)
{
	if (arg == NULL || arg->status->is_die)
		return (false);
	while (1)
	{
		if (ft_is_died(arg))
		{
			ft_die(arg);
			return (false);
		}
		check(pthread_mutex_lock(&arg->mutexes->queue));
		if (ft_my_empty(&arg->queue))
		{
			check(pthread_mutex_unlock(&arg->mutexes->queue));
			return (false);
		}
		else if (ft_my_top(&arg->queue) == arg->adrs_philo->id
			&& arg->settings->count_philo > 1)
		{
			ft_pop(&arg->queue);
			return (ft_get_forks(arg));
		}
		else
		{
			check(pthread_mutex_unlock(&arg->mutexes->queue));
			usleep(100);
			continue;
		}
	}
}

bool	ft_sleep(t_main	*env)
{
	if (env == NULL || env->status->is_die)
		return (false);
	ft_print_info(env, "is sleeping", "\033[93m");
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_die(env);
	if (env->status->is_die)
		return (false);
	return (true);
}

void	*main_action(void	*data)
{
	t_main	*arg;

	arg = (t_main *)data;
	arg->adrs_philo->time_last_eat = ft_get_now_time();
	while (arg->adrs_philo->count_iteration)
	{
		if (!ft_think(arg) || !ft_eat(arg) || !ft_sleep(arg))
			return (NULL);
		if (!arg->adrs_philo->is_infinity)
			--arg->adrs_philo->count_iteration;
	}
	return (NULL);
}
