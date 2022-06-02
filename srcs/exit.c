#include "header.h"

void	ft_fail(t_main	*env, const char	*message_error, bool	is_clean)
{
	if (env != NULL)
	{
		if (is_clean)
			ft_deinitial_all(env);
		if (message_error != NULL)
			write(STDERR_FILENO, message_error, ft_strlen(message_error));
	}
	exit(EXIT_FAILURE);
}

void	ft_success(t_main	*env)
{
	if (env != NULL)
		ft_deinitial_all(env);
	exit(EXIT_SUCCESS);
}
