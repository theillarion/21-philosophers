#include "header.h"

void	ft_initial_env(t_main	*env)
{
	if (env == NULL)
		return;
	env->settings = NULL;
	env->adrs_threads = NULL;
	env->critical = NULL;
	env->adrs_philo = NULL;
	env->adrs_main_struct = NULL;
	env->status = NULL;
}
