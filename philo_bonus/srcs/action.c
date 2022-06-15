#include "header.h"

void	ft_think(t_environment	*env)
{
	if (env == NULL || ft_is_died(env, NULL, NULL))
		ft_death(env);
	ft_print_info(env, "is thinking", "\033[96m");
}

void	ft_sleep(t_environment	*env)
{
	if (env == NULL || ft_is_died(env, NULL, NULL))
		ft_death(env);
	ft_print_info(env, "is sleeping", "\033[93m");
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_death(env);
}

void	ft_get_forks(t_environment	*env, sem_t	*fork)
{
	if (env == NULL || fork == NULL)
		ft_death(env);
	sem_wait(fork);
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (ft_is_died(env, fork, NULL))
		ft_death(env);
	sem_wait(fork);
	ft_print_info(env, "has taken a fork", "\033[95m");
	if (ft_is_died(env, fork, fork))
		ft_death(env);
}

void	ft_eat(t_environment	*env)
{
	if (env == NULL || ft_is_died(env, NULL, NULL))
		ft_death(env);
	ft_get_forks(env, env->semaphores->forks);
	ft_print_info(env, "is eating", "\033[92m");
	env->adrs_philo->time_last_eat = ft_get_now_time();
	if (!ft_smart_sleep(env, env->settings->time_to_eat))
		ft_death(env);
	sem_post(env->semaphores->forks);
	sem_post(env->semaphores->forks);
}

void	ft_main_action(t_environment	*env)
{
	env->semaphores->print = sem_open(env->names_semaphores->print, O_RDWR);
	env->semaphores->death = sem_open(env->names_semaphores->death, O_RDWR);
	env->semaphores->forks = sem_open(env->names_semaphores->forks, O_RDWR);
	env->adrs_philo->time_last_eat = ft_get_now_time();
	while (env->adrs_philo->count_iteration)
	{
		if (env->adrs_philo->id % 2 == 0)
			usleep(500);
		ft_think(env);
		ft_eat(env);
		ft_sleep(env);
		if (!env->adrs_philo->is_infinity)
			--env->adrs_philo->count_iteration;
	}
	exit(0);
}
