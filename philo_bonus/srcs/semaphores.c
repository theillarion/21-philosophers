#include "header.h"

sem_t	*ft_open_semaphore(const char	*name, unsigned int value)
{
	sem_t	*semaphore;

	semaphore = sem_open(name, O_CREAT | O_EXCL, 0600, value);
	if (semaphore == SEM_FAILED)
	{
		if (sem_unlink(name) != 0)
			return (NULL);
		semaphore = sem_open(name, O_CREAT | O_EXCL, 0600, value);
		if (semaphore == SEM_FAILED)
			semaphore = NULL;
	}
	return (semaphore);
}

char	*ft_get_name_semaphore(const char	*name)
{
	char			*result;
	char			*backup;
	char			*time_seconds;
	char			*time_microseconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_seconds = ft_itoa((int)time.tv_sec);
	time_microseconds = ft_itoa((int)time.tv_usec);
	result = ft_strjoin(name, "_");
	backup = result;
	result = ft_strjoin(result, time_seconds);
	ft_smart_free((void **)&backup);
	backup = result;
	result = ft_strjoin(result, "_");
	ft_smart_free((void **)&backup);
	backup = result;
	result = ft_strjoin(result, time_microseconds);
	ft_smart_free((void **)&backup);
	ft_smart_free((void **)&time_seconds);
	ft_smart_free((void **)&time_microseconds);
	return (result);
}

static void	ft_clear(pid_t	*pids, pid_t element, short count)
{
	short	i;

	if (pids == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		if (pids[i] == element)
		{
			pids[i] = 0;
			break ;
		}
		++i;
	}
	return ;
}

void	ft_wait(t_environment	*env)
{
	short	i;
	pid_t	pid;
	int		status;

	if (env == NULL)
		return ;
	i = 0;
	while (i < env->settings->count_philo)
	{
		pid = waitpid(-1, &status, 0);
		sem_wait(env->semaphores->print);
		ft_clear(env->pids, pid, env->settings->count_philo);
		if (pid == -1)
			ft_fail(env, "Rrror: waitpid\n", false);
		else if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		{
			ft_print_died(env, WEXITSTATUS(status) - 1);
			ft_success(env);
			break ;
		}
		sem_post(env->semaphores->print);
		++i;
	}
}
