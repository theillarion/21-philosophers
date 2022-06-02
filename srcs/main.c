#include "header.h"

int main(int argc, char	**argv)
{
	t_main 		*main;
	t_settings	settings;
	size_t 		i;

	main = NULL;
	if (!ft_read_args(&settings, argc - 1, (const char **)++argv))
		ft_fail(main, "Error\n", false);
	if (!ft_fill(&main, &settings))
		ft_fail(main, "Error\n", false);
	i = 0;
	while (i < main[0].settings->count_philo)
	{
		if (i == 0)
			settings.start_time = GetCurrentTime();
		check(pthread_create(&main->adrs_threads[i], NULL, main_action, &main[i]));
		++i;
	}
	i = 0;
	while (i < main->settings->count_philo)
	{
		check(pthread_join(main->adrs_threads[i], NULL));
		++i;
	}
	if (main->status->is_die)
		printf("\033[91m[%llu] #%zu died\033[0m\n", GetDifferenceCurrentTimeMs(&main->settings->start_time)/*, GetDifferenceMs(&main->settings->start_time, &main->status->time_die)*/, main->status->id);
	ft_success(main);
	return (0);
}
