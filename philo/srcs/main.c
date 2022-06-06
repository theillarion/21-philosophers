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
			settings.start_time = ft_get_now_time();
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
		ft_print_info(main, ft_get_difference_time_now_ms(&main->settings->start_time), main->status->id, "died", "\033[91m");
	ft_success(main);
	return (0);
}