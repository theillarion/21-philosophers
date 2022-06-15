#include "header.h"

bool	ft_fill_philos(t_philo	**philos, short count_philos,
			size_t count_iter)
{
	short	i;

	if (philos == NULL)
		return (false);
	*philos = (t_philo *)malloc(count_philos * sizeof(**philos));
	if (*philos == NULL)
		return (false);
	i = 0;
	while (i < count_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].is_infinity = count_iter == 0;
		(*philos)[i].count_iteration = count_iter
			+ (short)(*philos)[i].is_infinity;
		++i;
	}
	return (true);
}

bool	ft_fill_name_semaphores(t_name_semaphores	**name_semaphores)
{
	if (name_semaphores == NULL)
		return (false);
	*name_semaphores = (t_name_semaphores *)malloc(sizeof(**name_semaphores));
	if (*name_semaphores == NULL)
		return (false);
	(*name_semaphores)->print = ft_get_name_semaphore("print");
	(*name_semaphores)->death = ft_get_name_semaphore("death");
	(*name_semaphores)->forks = ft_get_name_semaphore("forks");
	return (true);
}

bool	ft_fill_semaphores(t_semaphores	**semaphores,
	const t_name_semaphores	*name_semaphores, short count_forks)
{
	if (semaphores == NULL || name_semaphores == NULL || count_forks == 0)
		return (false);
	(*semaphores) = (t_semaphores *)malloc(sizeof(**semaphores));
	if (*semaphores == NULL)
		return (false);
	(*semaphores)->print = ft_open_semaphore(name_semaphores->print, 1);
	if ((*semaphores)->print == NULL)
		return (false);
	(*semaphores)->death = ft_open_semaphore(name_semaphores->death, 1);
	if ((*semaphores)->death == NULL)
		return (false);
	(*semaphores)->forks
		= ft_open_semaphore(name_semaphores->forks, count_forks);
	if ((*semaphores)->forks == NULL)
		return (false);
	return (true);
}

bool	ft_fill_pids(pid_t	**pids, short count)
{
	if (pids == NULL)
		return (false);
	*pids = (pid_t *)malloc(count * sizeof(**pids));
	if (*pids == NULL)
		return (false);
	memset(*pids, 0, count * sizeof(**pids));
	return (true);
}

bool	ft_fill(t_environment	**env, t_settings	*settings)
{
	t_philo				*philos;
	t_name_semaphores	*name_semaphores;
	t_semaphores		*semaphores;
	pid_t				*pids;
	short				i;

	if (env == NULL || settings == NULL || settings->count_philo < 1)
		return (false);
	*env = (t_environment *)malloc(settings->count_philo * sizeof (**env));
	pids = (pid_t *)malloc(settings->count_philo * sizeof(*pids));
	if (*env == NULL || !ft_fill_name_semaphores(&name_semaphores)
		|| !ft_fill_semaphores(&semaphores,
			name_semaphores, settings->count_philo)
		|| !ft_fill_philos(&philos, settings->count_philo, settings->count_eat))
		return (false);
	i = -1;
	while (++i < settings->count_philo)
	{
		(*env)[i].pids = pids;
		(*env)[i].settings = settings;
		(*env)[i].names_semaphores = name_semaphores;
		(*env)[i].semaphores = semaphores;
		(*env)[i].adrs_philo = &philos[i];
	}
	return (true);
}
