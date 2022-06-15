#include "header.h"

int	main(int argc, char	**argv)
{
	t_environment	*main_env;
	t_settings		settings;
	short			i;

	if (!ft_read_args(&settings, argc - 1, (const char **)++argv)
		|| !ft_fill(&main_env, &settings))
		ft_fail(main_env, "Error\n", false);
	i = 0;
	while (i < main_env[0].settings->count_philo)
	{
		if (i == 0)
			settings.start_time = ft_get_now_time();
		main_env->pids[i] = fork();
		if (main_env->pids[i] < 0)
			ft_fail(main_env, "process", false);
		else if (main_env->pids[i] == 0)
			ft_main_action(&main_env[i]);
		else
			++i;
	}
	ft_wait(main_env);
	ft_success(main_env);
	return (0);
}
