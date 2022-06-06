#include "header.h"

static bool	ft_validation(const char	*str)
{
	size_t	count;
	size_t	i;

	i = 0;
	if (*str == '+')
		++str;
	count = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (false);
		++count;
	}
	if (count > 10 || count == 0
		|| (count == 10 && ft_strncmp(str, "2147483647", count) > 0))
		return (false);
	return (true);
}

bool	ft_read_args(t_settings	*settings, size_t argc, const char	**argv)
{
	size_t	i;

	if (argc < 4 || argc > 5)
		return (false);
	i = 0;
	while (i < argc)
		if (!ft_validation(argv[i++]))
			return false;
	settings->count_philo = ft_atoi(argv[0]);
	settings->time_to_die = ft_atoi(argv[1]);
	settings->time_to_eat = ft_atoi(argv[2]);
	settings->time_to_sleep = ft_atoi(argv[3]);
	settings->count_eat = 0;
	if (argc == 5)
		settings->count_eat = ft_atoi(argv[4]);
	return (true);
}
