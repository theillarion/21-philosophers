#include "header.h"

#define RED "\033[91m"
#define END "\033[0m"

void	ft_check_result(t_environment	*env, int code)
{
	if (code < 0)
	{
		sem_wait(env->semaphores->print);
		write(STDERR_FILENO, RED, strlen(RED));
		write(STDERR_FILENO, "error", 5);
		write(STDERR_FILENO, END, strlen(END));
		write(STDERR_FILENO, "\n", 1);
		sem_post(env->semaphores->print);
	}
}
