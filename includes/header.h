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
	size_t	id;
	size_t	left_fork;
	size_t	right_fork;
}			t_philo;

typedef struct s_forks
{
	pthread_mutex_t	*fork;
	bool			*is_used;
}					t_forks;

typedef struct s_settings
{
	t_time	start_time;
	size_t	count_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	count_eat;
	bool	is_end;
}			t_settings;

typedef struct s_critical
{
	t_forks			*forks;
	bool			is_end_game;
	pthread_mutex_t	mutex;
}					t_critical;

typedef	struct s_status
{
	bool			is_die;
	size_t			id;
	t_time			time_die;
	pthread_mutex_t	mutex_status;
}					t_status;

typedef struct s_main
{
	t_philo			*adrs_philo;
	pthread_t		*adrs_threads;
	t_status	*status;
	void			*adrs_main_struct;
	t_settings		*settings;
	t_critical		*critical;
}					t_main;

//		debug.c
void	print_philos(const t_philo	*philos, size_t	count);
void	print_settings(const t_settings	*settings);
void	print_critical(const t_critical	*critical, size_t count);
void	print_main(const t_main	*main);

//		utilities_int.c
int		ft_isdigit(int symbol);
int		ft_atoi(const char	*str);

//		utilities_string.c
size_t	ft_strlen(const char	*str);
int		ft_strncmp(const char	*str1, const char	*str2, size_t n);

//		exit.c
void	ft_fail(t_main	*env, const char	*message_error, bool	is_clean);
void	ft_success(t_main	*env);

//		fill.c
bool	ft_fill(t_main	**main, t_settings	*settings);

//		initial.c
void	ft_initial_env(t_main	*env);

//		deinitial.c
void	ft_smart_free(void	**memory);
void	ft_deinitial_all(t_main	*_main);

//		action.c
void	*main_action(void	*data);

//		validation.c
bool	ft_read_args(t_settings	*settings, size_t argc, const char	**argv);

//		check.c
void	check(int	code);

//		main.c
int		main(int argc, char	**argv);

#endif