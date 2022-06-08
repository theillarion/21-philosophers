#include "header.h"

#define RED "\033[91m"
#define END "\033[0m"

//	!!!	FORBIDDEN FUNCTION !!!

void	ft_check_result(t_main	*env, int code)
{
	if (code < 0)
	{
		pthread_mutex_lock(&env->mutexes->print);
		write(STDERR_FILENO, RED, strlen(RED));
		perror("Error: ");
		write(STDERR_FILENO, END, strlen(END));
		pthread_mutex_unlock(&env->mutexes->print);
	}
}
