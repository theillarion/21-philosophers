#include "header.h"

void	ft_swap(size_t 	*elem1, size_t	*elem2)
{
	size_t	temp;

	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
}

void	ft_fill_philos(t_philo	**philos, size_t	count_philos, size_t count_iter)
{
	size_t	i;

	if (philos == NULL)
		return ;
	*philos = (t_philo *)malloc(count_philos * sizeof(**philos));
	if (*philos == NULL)
		return ;
	i = 0;
	while (i < count_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].is_infinity = count_iter == 0;
		(*philos)[i].count_iteration = count_iter + (size_t)(*philos)[i].is_infinity;
		(*philos)[i].right_fork = i;
		if (i != 0)
			philos[0][i].left_fork = i - 1;
		else
			philos[0][i].left_fork = count_philos - 1;
		if (i % 2 != 0)
			ft_swap(&philos[0][i].left_fork, &philos[0][i].right_fork);
		++i;
	}
}

void	ft_fill_status(t_status	**status)
{
	if (status == NULL)
		return;
	*status = (t_status *)malloc(sizeof(**status));
	if (*status == NULL)
		return;
	(*status)->is_die = false;
	(*status)->id = 0;
}

void	ft_fill_mutexes(t_mutexes	**mutexes, size_t count)
{
	size_t	i;

	if (mutexes == NULL)
		return;
	*mutexes = (t_mutexes *)malloc(sizeof(**mutexes));
	if (*mutexes == NULL)
		return;
	(*mutexes)->fork = (pthread_mutex_t *)malloc(count * sizeof(*(*mutexes)->fork));
	if ((*mutexes)->fork == NULL)
		return;
	i = 0;
	while (i < count)
		pthread_mutex_init(&(*mutexes)->fork[i++], NULL);
	pthread_mutex_init(&(*mutexes)->queue, NULL);
	pthread_mutex_init(&(*mutexes)->all_forks, NULL);
	pthread_mutex_init(&(*mutexes)->print, NULL);
	pthread_mutex_init(&(*mutexes)->death, NULL);
}

void	ft_fill_queue(t_queue	**queue, size_t count)
{
	size_t	i;

	ft_init(queue, sizeof(size_t));
	i = 0;
	while (i < count)
	{
		if (i % 2 == 0)
			ft_my_push(queue, i);
		++i;
	}
	i = 0;
	while (i < count)
	{
		if (i % 2 != 0)
			ft_my_push(queue, i);
		++i;
	}
}

bool	ft_fill(t_main	**env, t_settings	*settings)
{
	pthread_t 	*threads;
	t_philo		*philos;
	t_status	*status;
	t_mutexes		*mutexes;
	t_queue 		*queue;
	size_t 		i;

	if (env == NULL || settings == NULL || settings->count_philo < 1)
		return (false);
	settings->is_end = false;
	ft_fill_queue(&queue, settings->count_philo);
	ft_fill_mutexes(&mutexes, settings->count_philo);
	ft_fill_philos(&philos, settings->count_philo, settings->count_eat);
	ft_fill_status(&status);
	threads = (pthread_t *)malloc(settings->count_philo * sizeof(*threads));
	*env = (t_main *)malloc(settings->count_philo * sizeof (**env));
	if (threads == NULL || *env == NULL || philos == NULL || status == NULL
		|| mutexes == NULL)
		return (false);
	i = 0;
	while (i < settings->count_philo)
	{
		(*env)[i].settings = settings;
		(*env)[i].status = status;
		(*env)[i].queue = queue;
		(*env)[i].mutexes = mutexes;
		(*env)[i].adrs_threads = threads;
		(*env)[i].adrs_philo = &philos[i];
		++i;
	}
	return (true);
}
