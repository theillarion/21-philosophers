#include "header.h"

void	ft_initial_env(t_environment	*env)
{
	if (env == NULL)
		return ;
	env->settings = NULL;
	env->adrs_threads = NULL;
	env->adrs_philo = NULL;
	env->status_death = NULL;
	env->mutexes = NULL;
}
