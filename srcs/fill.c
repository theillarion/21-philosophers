#include "header.h"

void	ft_swap(size_t 	*elem1, size_t	*elem2)
{
	size_t	temp;

	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
}

void	ft_fill_philos(t_philo	**philos, size_t	count)
{
	size_t	i;

	if (philos == NULL)
		return ;
	*philos = (t_philo *)malloc(count * sizeof(**philos));
	if (*philos == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		philos[0][i].id = i;
		if (i != 0)
			philos[0][i].left_fork = i - 1;
		else
			philos[0][i].left_fork = count - 1;
		philos[0][i].right_fork = i;
		if (i % 2 != 0)
			ft_swap(&philos[0][i].left_fork, &philos[0][i].right_fork);
		++i;
	}
}

void	ft_fill_settings(t_settings 	**settings)
{
	if (settings == NULL)
		return ;
	*settings = (t_settings *)malloc(sizeof (**settings));
	if (*settings == NULL)
		return ;
	(*settings)->count_philo = 10;
	(*settings)->count_eat = 0;
	(*settings)->time_to_die = 100;
	(*settings)->time_to_eat = 1;
	(*settings)->time_to_sleep = 100;
	(*settings)->start_time = GetCurrentTime();
	(*settings)->is_end = false;
}

void	ft_fill_critical(t_critical	**critical, size_t count)
{
	size_t	i;

	if (critical == NULL)
		return;
	*critical = (t_critical *)malloc(sizeof(**critical));
	if (*critical == NULL)
		return ;
	(*critical)->forks = (t_forks *)malloc(sizeof(*(*critical)->forks));
	if ((*critical)->forks == NULL)
		return ;
	(*critical)->forks->fork = (pthread_mutex_t *)malloc(count * sizeof(*(*critical)->forks->fork));
	if ((*critical)->forks->fork == NULL)
		return ;
	(*critical)->forks->is_used = (bool *)malloc(count * sizeof(*(*critical)->forks->is_used));
	if ((*critical)->forks->is_used == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		(*critical)->forks->is_used[i] = false;
		check(pthread_mutex_init(&(*critical)->forks->fork[i++], 0));
	}
	(*critical)->is_end_game = false;
	check(pthread_mutex_init(&(*critical)->mutex, 0));
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
	(*status)->time_die = GetCurrentTime();
	check(pthread_mutex_init(&(*status)->mutex_status, NULL));
}

bool	ft_fill(t_main	**env, t_settings	*settings)
{
	pthread_t 	*threads;
	t_critical	*critical;
	t_philo		*philos;
	t_status	*status;
	size_t 		i;

	if (env == NULL || settings == NULL)
		return (false);
	settings->is_end = false;
	ft_fill_critical(&critical, settings->count_philo);
	ft_fill_philos(&philos, settings->count_philo);
	ft_fill_status(&status);
	threads = (pthread_t *)malloc(settings->count_philo * sizeof(*threads));
	*env = (t_main *)malloc(settings->count_philo * sizeof (**env));
	if (threads == NULL || *env == NULL || critical == NULL || philos == NULL)
		return (false);
	i = 0;
	while (i < settings->count_philo)
	{
		(*env)[i].settings = settings;
		(*env)[i].status = status;
		(*env)[i].adrs_threads = threads;
		(*env)[i].adrs_philo = &philos[i];
		(*env)[i].critical = critical;
		(*env)[i].adrs_main_struct = (void *)env;
		++i;
	}
	return (true);
}

/*void	ft_create_philo(t_philo	**philo, size_t	id, size_t all_count)
{
	if (philo != NULL)
	{
		*philo = (t_philo *)malloc(sizeof(**philo));
		if (*philo == NULL)
			return ;
		(*philo)->id = id;
		if (id != 0)
			(*philo)->left_fork = id - 1;
		else
			(*philo)->left_fork = all_count - 1;
		(*philo)->right_fork = id;
	}

}*/

/*void	ft_fill_forks(t_forks	**forks, size_t count)
{
	size_t i;

	*forks = (t_forks *)malloc(sizeof(**forks));
	(*forks)->forks = (pthread_mutex_t *)malloc(count * sizeof(*(*forks)->forks));
	(*forks)->is_used = (bool *)malloc(count * sizeof(*(*forks)->is_used));
	i = 0;
	while (i < count)
	{
		(*forks)->is_used[i] = false;
		check(pthread_mutex_init(&(*forks)->forks[i], 0));
		++i;
	}
}*/
