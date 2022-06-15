#include "header.h"

void	ft_destroy_name_semaphores(t_name_semaphores	**name_semaphores)
{
	if (name_semaphores == NULL || *name_semaphores == NULL)
		return ;
	if ((*name_semaphores)->print != NULL)
		sem_unlink((*name_semaphores)->print);
	ft_smart_free((void **)&(*name_semaphores)->print);
	if ((*name_semaphores)->death != NULL)
		sem_unlink((*name_semaphores)->death);
	ft_smart_free((void **)&(*name_semaphores)->death);
	if ((*name_semaphores)->forks != NULL)
		sem_unlink((*name_semaphores)->forks);
	ft_smart_free((void **)&(*name_semaphores)->forks);
	memset(*name_semaphores, 0, sizeof(**name_semaphores));
	ft_smart_free((void **)name_semaphores);
}

void	ft_smart_close(sem_t	**semaphore)
{
	if (semaphore != NULL)
	{
		sem_close(*semaphore);
		*semaphore = NULL;
	}
}

void	ft_destroy_semaphores(t_semaphores	**semaphores)
{
	if (semaphores == NULL || *semaphores == NULL)
		return ;
	ft_smart_close(&(*semaphores)->print);
	ft_smart_close(&(*semaphores)->death);
	ft_smart_close(&(*semaphores)->forks);
	ft_smart_free((void **)semaphores);
}

void	ft_destroy_pids(pid_t	**pids, short count)
{
	short	i;

	if (pids == NULL || *pids == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		if ((*pids)[i] != 0)
			kill((*pids)[i], SIGTERM);
		++i;
	}
	ft_smart_free((void **)pids);
}

void	ft_deinitial_all(t_environment	*env)
{
	short	count;

	if (env == NULL)
		return ;
	count = env->settings->count_philo;
	ft_destroy_semaphores(&env->semaphores);
	ft_destroy_pids(&env->pids, count);
	ft_destroy_name_semaphores(&env->names_semaphores);
	if (env->adrs_philo != NULL)
		memset(env->adrs_philo, 0, count * sizeof(*env->adrs_philo));
	ft_smart_free((void **)&env->adrs_philo);
	memset(env, 0, count * sizeof(*env));
	ft_smart_free((void **)&env);
}
