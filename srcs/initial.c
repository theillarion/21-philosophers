#include "header.h"

void	ft_initial_philos(t_philo	**philos, size_t	count)
{
	*philos = (t_philo *)malloc(count * sizeof(**philos));
	for (size_t i = 0; i < count; ++i)
	{
		philos[0][i].id = i;
		if (i != 0)
			philos[0][i].left_fork = i - 1;
		else
			philos[0][i].left_fork = count - 1;
		philos[0][i].right_fork = i;
	}
}

void	ft_initial_forks(t_forks	**forks, size_t count)
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
}

void	ft_initial_settings(t_settings 	**settings)
{
	*settings = (t_settings *)malloc(sizeof (**settings));
	(*settings)->count_philo = 5;
	(*settings)->count_eat = 3;
	(*settings)->time_to_die = 100;
	(*settings)->time_to_eat = 10;
	(*settings)->time_to_sleep = 100;
	(*settings)->start_time = GetCurrentTime();
	(*settings)->is_end = false;
}

void	ft_main_initial(t_main	*main)
{
	ft_initial_settings(&main->settings);
	ft_initial_forks(&main->critical.forks, main->settings->count_philo);
	pthread_mutex_init(&main->critical.mutex, NULL);
}
