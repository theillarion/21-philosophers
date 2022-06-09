#include "header.h"

int	main(int argc, char	**argv)
{
	t_environment	*main_env;
	t_settings		settings;
	short			i;

	if (!ft_read_args(&settings, argc - 1, (const char **)++argv))
		ft_fail(main_env, "Error\n", false);
	if (!ft_fill(&main_env, &settings))
		ft_fail(main_env, "Error\n", false);
	i = 0;
	while (i < main_env[0].settings->count_philo)
	{
		if (i == 0)
			settings.start_time = ft_get_now_time();
		ft_check_result(main_env, pthread_create(&main_env->adrs_threads[i],
				NULL, ft_main_action, &main_env[i]));
		++i;
	}
	i = 0;
	while (i < main_env->settings->count_philo)
		ft_check_result(main_env, pthread_join(main_env->adrs_threads[i++],
				NULL));
	if (main_env->status_death->is_die)
		ft_print_died(main_env);
	ft_success(main_env);
	return (0);
}

/*
	while (!ft_my_empty(&main_env->queue))
	{
		printf("%zu\n", ft_my_top(&main_env->queue));
		ft_pop(&main_env->queue);
	}
*/

/* 	fd = open("action.log", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		char	*err = strerror(errno);
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, err, strlen(err));
		exit(EXIT_FAILURE);
	} */