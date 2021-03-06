#include "header.h"

// [ DEBUG ]
void	print_philos(const t_philo	*philos, size_t	count)
{

	for (size_t i = 0; i < count; ++i)
		printf("Philo №%ld:\nAddress: %p\nLeft: %ld\nRight: %ld\n\n", philos[i].id, philos, philos[i].left_fork, philos[i].right_fork);
}

void	print_settings(const t_settings	*settings)
{
	printf("\033[92mSettings\033[0m\nAddress: %p\n"
		   "Start time: %ld,%ld\nCount philo: %zu\n"
		   "Time to eat: %zu\nTime to sleep: %zu\n"
		   "Time to die: %zu\nCount eat: %zu\nIs end: %d\n",
		   settings, settings->start_time.tv_sec,
		   settings->start_time.tv_usec,
		   settings->count_philo, settings->time_to_eat,
		   settings->time_to_sleep, settings->time_to_die,
		   settings->count_eat, settings->is_end);
}

void	print_main(const t_main	*main)
{
	printf("\033[92mPhilo\033[0m\nAddress: %p\n"
		   "Id: %zu\nLeft: %zu\nRight: %zu\n\n",
		   main->adrs_philo, main->adrs_philo->id,
		   main->adrs_philo->left_fork, main->adrs_philo->right_fork);
	print_settings(main->settings);
}

void	print_queue(const t_queue	**queue)
{
	t_node	*current;

	current = (*queue)->head;
	printf("Queue:\n");
	while (current != NULL)
	{
		printf("%zu\n", *(size_t *)current->element);
		current = current->next;
	}
}
