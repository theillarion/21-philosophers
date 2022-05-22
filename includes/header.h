#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include "time.h"
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

enum	e_state
{
	HUNGRY,
	THINKING,
	EATING,
	SLEEPING,
};

typedef struct s_philo
{
	size_t			id;
	size_t			left_fork;
	size_t			right_fork;
}			t_philo;

typedef struct s_forks
{
	pthread_mutex_t	*forks;
	bool			*is_used;
}		t_forks;

typedef struct s_settings
{
	t_time	start_time;
	size_t	count_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	count_eat;
	bool	is_end;
}		t_settings;

typedef struct s_main
{
	t_philo			*adrs_philo;
	t_settings		*settings;
	struct s_critical
	{
		t_forks			*forks;
		pthread_mutex_t	mutex;
	}	critical;
}	t_main;

void	*main_action(void	*data);
void	ft_initial_philos(t_philo	**philos, size_t	count);
void	check(int	code);
void	ft_main_initial(t_main	*main);
int		main(void);

#endif