#include "header.h"

void	ft_set_all(t_main	*env, bool set_flag)
{
	size_t	i;

	if (env == NULL)
		return ;
	i = 0;
	while (i < env->stats_eat->count_all)
		env->stats_eat->philo_eat[i++] = set_flag;
}

void	ft_add_stats_eat(t_main	*env)
{
	if (env == NULL)
		return ;
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->count_ate));
	env->stats_eat->philo_eat[env->adrs_philo->id] = true;
	++env->stats_eat->count_ate;
	if (env->stats_eat->count_ate == env->stats_eat->count_all)
	{
		env->stats_eat->count_ate = 0;
		memset(env->stats_eat->philo_eat, 0, env->settings->count_philo
			* sizeof(*env->stats_eat->philo_eat));
	}
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->count_ate));
}

bool	ft_die(t_main	*env)
{
	if (env == NULL)
		return (false);
	ft_check_result(env, pthread_mutex_lock(&env->mutexes->death));
	if (env->status->is_die)
	{
		ft_check_result(env, pthread_mutex_unlock(&env->mutexes->death));
		return (false);
	}
	env->status->is_die = true;
	env->status->id = env->adrs_philo->id;
	ft_check_result(env, pthread_mutex_unlock(&env->mutexes->death));
	return (false);
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

bool	ft_get_fork(t_main	*env, bool is_first_fork)
{
	if (env == NULL)
		return (false);
	if (is_first_fork)
		ft_check_result(env, pthread_mutex_lock(
				&env->mutexes->fork[env->adrs_philo->right_fork]));
	else
		ft_check_result(env, pthread_mutex_lock(
				&env->mutexes->fork[env->adrs_philo->left_fork]));
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (env->status->is_die
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (!env->status->is_die)
			ft_die(env);
		if (!is_first_fork)
			ft_check_result(env, pthread_mutex_unlock(
					&env->mutexes->fork[env->adrs_philo->left_fork]));
		ft_check_result(env, pthread_mutex_unlock(
				&env->mutexes->fork[env->adrs_philo->right_fork]));
		//ft_check_result(env, pthread_mutex_unlock(&env->mutexes->all_forks));
		//ft_check_result(env, pthread_mutex_unlock(&env->mutexes->queue));
		return (false);
	}
	return (true);
}

bool	ft_check_death(t_main	*env, pthread_mutex_t	*mutex1,
			pthread_mutex_t	*mutex2)
{
	if (env == NULL)
		return (false);
	if (env->status->is_die
		|| ft_get_difference_time_now_ms(&env->adrs_philo->time_last_eat)
		>= env->settings->time_to_die)
	{
		if (!env->status->is_die)
			ft_die(env);
		if (mutex1 != NULL)
			ft_check_result(env, pthread_mutex_unlock(mutex1));
		if (mutex2 != NULL)
			ft_check_result(env, pthread_mutex_unlock(mutex2));
		return (false);
	}
	return (true);
}

bool	ft_get_forks(t_main	*env)
{
	if (!ft_check_death(env, /*&env->mutexes->queue*/NULL, NULL))
		return (false);
	//ft_pop(&env->queue);
	//ft_check_result(env, pthread_mutex_lock(&env->mutexes->all_forks));
	if (!ft_get_fork(env, true))
		return (false);
	if (!ft_get_fork(env, false))
		return (false);
	//ft_check_result(env, pthread_mutex_unlock(&env->mutexes->all_forks));
	//ft_my_push(&env->queue, env->adrs_philo->id);
	//ft_check_result(env, pthread_mutex_unlock(&env->mutexes->queue));
	ft_print_info(env, "is eating", "\033[92m");
	env->adrs_philo->time_last_eat = ft_get_now_time();
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_die(env);
	ft_add_stats_eat(env);
	ft_check_result(env, pthread_mutex_unlock(
			&env->mutexes->fork[env->adrs_philo->left_fork]));
	ft_check_result(env, pthread_mutex_unlock(
			&env->mutexes->fork[env->adrs_philo->right_fork]));
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
			return (ft_die(arg));
		ft_check_result(arg, pthread_mutex_lock(&arg->mutexes->count_ate));
		if (arg->stats_eat->philo_eat[arg->adrs_philo->id] == false)
		{
			ft_check_result(arg, pthread_mutex_unlock(&arg->mutexes->count_ate));
			return (ft_get_forks(arg));
		}
		else
		{
			ft_check_result(arg, pthread_mutex_unlock(&arg->mutexes->count_ate));
			usleep(100);
			continue ;
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
		if (arg->adrs_philo->id % 2 != 0)
			usleep(100);
		if (!ft_think(arg) || !ft_eat(arg) || !ft_sleep(arg))
			return (NULL);
		if (!arg->adrs_philo->is_infinity)
			--arg->adrs_philo->count_iteration;
	}
	return (NULL);
}
