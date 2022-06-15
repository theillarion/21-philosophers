#include "header.h"

void	ft_initial_env(t_environment	*env)
{
	if (env == NULL)
		return ;
	env->pids = NULL;
	env->adrs_philo = NULL;
	env->settings = NULL;
	env->semaphores = NULL;
	env->names_semaphores = NULL;
}
