#include "header.h"

void	ft_initial_env(t_main	*env)
{
	if (env == NULL)
		return;
	env->settings = NULL;
	env->adrs_threads = NULL;
	env->adrs_philo = NULL;
	env->status = NULL;
	env->mutexes = NULL;
	env->queue = NULL;
}
