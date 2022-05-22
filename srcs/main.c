#include "header.h"

// [ DEBUG ]
void	print_philos(const t_philo	*philos, size_t	count)
{
	printf("Philos\n");
	for (size_t i = 0; i < count; ++i)
		printf("Philo №%ld:\nLeft: %ld\nRight: %ld\n\n", philos[i].id, philos[i].left_fork, philos[i].right_fork);
}

int main(void)
{
	pthread_t	*threads;
	t_philo		*philos = NULL;
	t_main 		main;
	size_t 		i;

	ft_main_initial(&main);
	ft_initial_philos(&philos, main.settings->count_philo);
	//print_philos(philos, main.settings->count_philo);
	threads	= (pthread_t *)malloc(main.settings->count_philo * sizeof(*threads));
	i = 0;
	while (i < main.settings->count_philo)
	{
		main.adrs_philo = &philos[i];
		//if (i == 0)
		//	main.settings->start_time = GetCurrentTime();
		check(pthread_create(&threads[i], NULL, main_action, &main));
		++i;
	}

	i = 0;
	while (i < main.settings->count_philo)
	{
		check(pthread_join(threads[i], NULL));
		++i;
	}
	return (0);
}
