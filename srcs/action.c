#include "header.h"

void	ft_die(t_main	*env)
{
	if (env == NULL)
		return;
	check(pthread_mutex_lock(&env->status->mutex_status));
	if (env->status->is_die)
	{
		check(pthread_mutex_unlock(&env->status->mutex_status));
		return;
	}
	env->status->is_die = true;
	env->status->id = env->adrs_philo->id;
	env->status->time_die = GetCurrentTime();
	check(pthread_mutex_unlock(&env->status->mutex_status));
}

bool	ft_think(t_main	*arg, const t_time	*time_start)
{
	if (arg == NULL)
		return (false);
	if (arg->status->is_die)
		return (false);
	if (GetDifferenceCurrentTimeMs(time_start) > arg->settings->time_to_die)
	{
		ft_die(arg);
		return (false);
	}
	printf("\033[93m[%llu] #%zu is thinking\033[0m\n", GetDifferenceCurrentTimeMs(&arg->settings->start_time), arg->adrs_philo->id);
	return (true);
}

bool	ft_get_fork(t_main	*env, const t_time	*start_time_eat, bool is_first_fork)
{
	if (env == NULL)
		return (false);
	if (is_first_fork)
		check(pthread_mutex_lock(&env->critical->forks->fork[env->adrs_philo->left_fork]));
	else
		check(pthread_mutex_lock(&env->critical->forks->fork[env->adrs_philo->right_fork]));
	printf("[%llu] #%zu has taken a fork\n", GetDifferenceCurrentTimeMs(&env->settings->start_time), env->adrs_philo->id);
	if (env->status->is_die || GetDifferenceCurrentTimeMs(start_time_eat) >= env->settings->time_to_eat)
	{
		if (!env->status->is_die)
			ft_die(env);
		if (!is_first_fork)
			check(pthread_mutex_unlock(&env->critical->forks->fork[env->adrs_philo->right_fork]));
		check(pthread_mutex_unlock(&env->critical->forks->fork[env->adrs_philo->left_fork]));
		check(pthread_mutex_unlock(&env->critical->mutex));
		return (false);
	}
	return (true);
}

bool	ft_get_forks(t_main	*env, const t_time	*start_time_eat, t_time	*end_time_eat)
{
	if (env == NULL)
		return (false);
	if (env->status->is_die)
		return (false);
	check(pthread_mutex_lock(&env->critical->mutex));
	if (env->status->is_die || GetDifferenceCurrentTimeMs(start_time_eat) >= env->settings->time_to_eat)
	{
		if (!env->status->is_die)
			ft_die(env);
		check(pthread_mutex_unlock(&env->critical->mutex));
		return (false);
	}
	if (!ft_get_fork(env, start_time_eat, true))
		return (false);
	if (!ft_get_fork(env, start_time_eat, false))
		return (false);
	check(pthread_mutex_unlock(&env->critical->forks->fork[env->adrs_philo->right_fork]));
	check(pthread_mutex_unlock(&env->critical->forks->fork[env->adrs_philo->left_fork]));
	check(pthread_mutex_unlock(&env->critical->mutex));
	if (env->status->is_die)
		return (false);
	*end_time_eat = GetCurrentTime();
	return (true);
}

bool	ft_eat(t_main	*arg, t_time	*end_time_eat)
{
	t_time	start_time_eat;

	if (arg == NULL)
		return (false);

	if (arg->status->is_die)
		return (false);
	start_time_eat = GetCurrentTime();
	printf("\033[92m[%llu] #%zu is eating\033[0m\n", GetDifferenceMs(&arg->settings->start_time, &start_time_eat), arg->adrs_philo->id);
	return (ft_get_forks(arg, &start_time_eat, end_time_eat));
}

bool	ft_sleep(t_main	*env, const t_time	*time_start)
{
	size_t	count_ms;

	if (env == NULL)
		return (false);
	if (env->status->is_die)
		return (false);
	printf("\033[93m[%llu] #%zu is sleeping\033[0m\n", GetDifferenceCurrentTimeMs(&env->settings->start_time), env->adrs_philo->id);
	count_ms = 0;
	while (!env->status->is_die && count_ms < env->settings->time_to_sleep)
	{
		if (GetDifferenceCurrentTimeMs(time_start) > env->settings->time_to_die)
		{
			ft_die(env);
			return (false);
		}
		usleep(1000);
		++count_ms;
	}
	if (env->status->is_die)
		return (false);
	return (true);
}

void	*main_action(void	*data)
{
	t_main	*arg;
	t_time	start_time;
	bool	is_count;
	size_t	i;

	arg = (t_main *)data;
	is_count = true;
	if (arg->settings->count_eat == 0)
		is_count = false;
	i = 1;
	start_time = GetCurrentTime();
	while (i)
	{
		if (!ft_think(arg, &start_time) || !ft_eat(arg, &start_time) || !ft_sleep(arg, &start_time))
			return (NULL);
		if (is_count)
		{
			if (i == arg->settings->count_eat)
				return (NULL);
			++i;
		}
	}
	return (NULL);
}
