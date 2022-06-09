#include "header.h"

/* void	ft_swap(size_t	*elem1, size_t	*elem2)
{
	size_t	temp;

	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
} */

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
		(*philos)[i].right_fork = i;
		(*philos)[i].left_fork = (i + 1) % count_philos;
		++i;
	}
	return (true);
}

bool	ft_fill_status_death(t_status_death	**status_death)
{
	if (status_death == NULL)
		return (false);
	*status_death = (t_status_death *)malloc(sizeof(**status_death));
	if (*status_death == NULL)
		return (false);
	(*status_death)->is_die = false;
	(*status_death)->id = 0;
	return (true);
}

bool	ft_fill_mutexes(t_mutexes	**mutexes, short count)
{
	short	i;

	if (mutexes == NULL)
		return (false);
	*mutexes = (t_mutexes *)malloc(sizeof(**mutexes));
	if (*mutexes == NULL)
		return (false);
	(*mutexes)->fork = (pthread_mutex_t *)malloc(count
			* sizeof(*(*mutexes)->fork));
	if ((*mutexes)->fork == NULL)
		return (false);
	i = 0;
	while (i < count)
		pthread_mutex_init(&(*mutexes)->fork[i++], NULL);
	pthread_mutex_init(&(*mutexes)->print, NULL);
	pthread_mutex_init(&(*mutexes)->death, NULL);
	return (true);
}

bool	ft_fill(t_environment	**env, t_settings	*settings)
{
	pthread_t		*threads;
	t_philo			*philos;
	t_status_death	*status_death;
	t_mutexes		*mutexes;
	short			i;

	if (env == NULL || settings == NULL || settings->count_philo < 1)
		return (false);
	*env = (t_environment *)malloc(settings->count_philo * sizeof (**env));
	threads = (pthread_t *)malloc(settings->count_philo * sizeof(*threads));
	if (threads == NULL || *env == NULL
		|| !ft_fill_philos(&philos, settings->count_philo, settings->count_eat)
		|| !ft_fill_mutexes(&mutexes, settings->count_philo)
		|| !ft_fill_status_death(&status_death))
		return (false);
	i = -1;
	while (++i < settings->count_philo)
	{
		(*env)[i].settings = settings;
		(*env)[i].status_death = status_death;
		(*env)[i].mutexes = mutexes;
		(*env)[i].adrs_threads = threads;
		(*env)[i].adrs_philo = &philos[i];
	}
	return (true);
}
