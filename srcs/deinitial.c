#include "header.h"

void	ft_smart_free(void	**memory)
{
	if (memory != NULL && *memory != NULL)
	{
		free(*memory);
		*memory = NULL;
	}
}

static void	ft_deinital_critical(t_critical	**critical, size_t count)
{
	size_t	i;

	if (critical != NULL && *critical != NULL)
	{
		i = 0;
		while (i < count)
			pthread_mutex_destroy(&(*critical)->forks->fork[i++]);
		pthread_mutex_destroy(&(*critical)->mutex);
		memset((*critical)->forks->is_used, 0, count * sizeof(*(*critical)->forks->is_used));
		ft_smart_free((void **)&(*critical)->forks->is_used);
		memset((*critical)->forks->fork, 0, count * sizeof(*(*critical)->forks->fork));
		ft_smart_free((void **)&(*critical)->forks->fork);
		memset((*critical)->forks, 0, sizeof(*(*critical)->forks));
		ft_smart_free((void **)&(*critical)->forks);
	}
}

void	ft_deinitial_all(t_main	*_main)
{
	t_main	**main_struct;
	size_t 	count;

	if (_main != NULL)
	{
		main_struct = (t_main **)_main->adrs_main_struct;
		count = (*main_struct)->settings->count_philo;
		memset((*main_struct)->adrs_philo, 0, count * sizeof(*(*main_struct)->adrs_philo));
		ft_smart_free((void **)&(*main_struct)->adrs_philo);
		check(pthread_mutex_destroy(&((*main_struct)->status)->mutex_status));
		memset((*main_struct)->status, 0, sizeof(*(*main_struct)->status));
		ft_smart_free((void **)&(*main_struct)->status);
		ft_deinital_critical(&(*main_struct)->critical, count);
		memset((*main_struct)->critical, 0, sizeof(*(*main_struct)->critical));
		ft_smart_free((void **)&(*main_struct)->critical);
		memset((*main_struct)->adrs_threads, 0, count * sizeof(*(*main_struct)->adrs_threads));
		ft_smart_free((void **)&(*main_struct)->adrs_threads);
		memset(*main_struct, 0, count * sizeof(**main_struct));
		free(*main_struct);
	}
}
