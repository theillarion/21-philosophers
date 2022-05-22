#include "header.h"

void	ft_think(const t_main	*arg)
{
	t_time	now_time;

	if (arg != NULL)
	{
		now_time = GetCurrentTime();
		printf("\033[93m[%llu] #%zu is thinking\033[0m\n", GetDifferenceMs(&arg->settings->start_time, &now_time), arg->adrs_philo->id);
	}
}

void	ft_eat(t_main	*arg)
{
	t_time	time_start_eat;

	if (arg != NULL)
	{
		if (arg->settings->is_end)
			return;
		time_start_eat = GetCurrentTime();
		printf("\033[92m[%llu] #%zu is eating\033[0m\n", GetDifferenceMs(&arg->settings->start_time, &time_start_eat), arg->adrs_philo->id);
		while (1)
		{
			if (arg->settings->is_end)
				return;

			check(pthread_mutex_lock(&arg->critical.mutex));
			if (GetDifferenceCurrentTimeMs(&time_start_eat) >= arg->settings->time_to_eat)
			{
				arg->settings->is_end = true;
				//printf("Time to eat: %zu\nTime start: %ld,%ld\n", arg->all_time->time_to_eat, time_start_eat.tv_sec, time_start_eat.tv_usec);
				printf("\033[91m[%llu] #%zu died\033[0m\n", GetDifferenceCurrentTimeMs(&time_start_eat), arg->adrs_philo->id);
				check(pthread_mutex_unlock(&arg->critical.mutex));
				return ;
			}
			if (arg->critical.forks->is_used[arg->adrs_philo->left_fork] || arg->critical.forks->is_used[arg->adrs_philo->right_fork])
			{
				check(pthread_mutex_unlock(&arg->critical.mutex));
				continue;
			}
			check(pthread_mutex_lock(&arg->critical.forks->forks[arg->adrs_philo->left_fork]));
			arg->critical.forks->is_used[arg->adrs_philo->left_fork] = true;
			printf("[%llu] #%zu has taken a fork\n", GetDifferenceCurrentTimeMs(&arg->settings->start_time), arg->adrs_philo->id);
			check(pthread_mutex_lock(&arg->critical.forks->forks[arg->adrs_philo->right_fork]));
			arg->critical.forks->is_used[arg->adrs_philo->right_fork] = true;
			printf("[%llu] #%zu has taken a fork\n", GetDifferenceCurrentTimeMs(&arg->settings->start_time), arg->adrs_philo->id);
			arg->critical.forks->is_used[arg->adrs_philo->right_fork] = false;
			check(pthread_mutex_unlock(&arg->critical.forks->forks[arg->adrs_philo->right_fork]));
			arg->critical.forks->is_used[arg->adrs_philo->left_fork] = false;
			check(pthread_mutex_unlock(&arg->critical.forks->forks[arg->adrs_philo->left_fork]));
			check(pthread_mutex_unlock(&arg->critical.mutex));
			return ;
		}
	}
}

void	*main_action(void	*data)
{
	t_main	*arg;
	bool	is_count;
	size_t	i;

	arg = (t_main *)data;
	if (arg->settings->is_end)
		return NULL;
	is_count = true;
	if (arg->settings->count_eat == 0)
		is_count = false;
	i = 1;
	while (i)
	{
		ft_think(arg);
		ft_eat(arg);
		if (arg->settings->is_end)
			return NULL;
		printf("\033[93m[%llu] #%zu is sleeping\033[0m\n", GetDifferenceCurrentTimeMs(&arg->settings->start_time), arg->adrs_philo->id);
		usleep(arg->settings->time_to_sleep * 1000);
		if (arg->settings->is_end)
			return NULL;
		if (is_count)
		{
			if (i == arg->settings->count_eat)
				return (NULL);
			++i;
		}
	}
	return (NULL);
}
