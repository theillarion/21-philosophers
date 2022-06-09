#include "header.h"

void	ft_destroy_mutexes(t_mutexes	**mutexes, size_t count)
{
	size_t	i;

	if (mutexes == NULL || *mutexes == NULL)
		return ;
	i = 0;
	while (i < count)
		pthread_mutex_destroy(&(*mutexes)->fork[i++]);
	if ((*mutexes)->fork != NULL)
		memset((*mutexes)->fork, 0, count * sizeof(*(*mutexes)->fork));
	ft_smart_free((void **)&(*mutexes)->fork);
	pthread_mutex_destroy(&(*mutexes)->print);
	pthread_mutex_destroy(&(*mutexes)->death);
	if (*mutexes != NULL)
		memset(*mutexes, 0, sizeof(**mutexes));
	ft_smart_free((void **)mutexes);
}

void	ft_deinitial_all(t_environment	*env)
{
	size_t	count;

	if (env == NULL)
		return ;
	count = env->settings->count_philo;
	ft_destroy_mutexes(&env->mutexes, count);
	if (env->adrs_philo != NULL)
		memset(env->adrs_philo, 0, count * sizeof(*env->adrs_philo));
	ft_smart_free((void **)&env->adrs_philo);
	if (env->status_death != NULL)
		memset(env->status_death, 0, sizeof(*env->status_death));
	ft_smart_free((void **)&env->status_death);
	if (env->adrs_philo != NULL)
		memset(env->adrs_threads, 0, count * sizeof(*env->adrs_threads));
	ft_smart_free((void **)&env->adrs_threads);
	memset(env, 0, count * sizeof(*env));
	ft_smart_free((void **)&env);
}
