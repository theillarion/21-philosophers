#include "header.h"

#define RED "\033[91m"
#define END "\033[0m"

//	!!!	FORBIDDEN FUNCTION !!!

void	check(int	code)
{
	if (code < 0)
	{
		write(STDERR_FILENO, RED, strlen(RED));
		perror("Error: ");
		write(STDERR_FILENO, END, strlen(END));
	}
}
