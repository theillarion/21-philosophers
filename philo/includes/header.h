#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include "../libs/queue/includes/queue.h"

typedef struct timeval		t_time;
typedef unsigned long long	t_u64int;

typedef struct s_philo
{
	size_t	id;
	size_t	left_fork;
	size_t	right_fork;
	t_time	time_last_eat;
	size_t	count_iteration;
	bool	is_infinity;
	bool	is_ate;
}			t_philo;

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

typedef struct s_status
{
	bool			is_die;
	size_t			id;
}					t_status;

typedef struct s_mutexes
{
	pthread_mutex_t	queue;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	all_forks;
	pthread_mutex_t	*fork;
	pthread_mutex_t	count_ate;
}					t_mutexes;

typedef struct s_map
{
	size_t	id;
	bool	is_ate;
}	t_map;

typedef struct s_stats_eat
{
	bool	*philo_eat;
	size_t	count_ate;
	size_t	count_all;
}	t_stats_eat;

typedef struct s_main
{
	t_philo			*adrs_philo;
	pthread_t		*adrs_threads;
	t_status		*status;
	t_settings		*settings;
	t_mutexes		*mutexes;
	t_queue			*queue;
	t_queue			*orig_queue;
	t_stats_eat		*stats_eat;
}					t_main;

//			time.c
t_u64int	ft_get_difference_time_ms(const t_time	*time1,
				const t_time	*time2);
t_u64int	ft_get_difference_time_now_ms(const t_time	*time);
t_time		ft_get_now_time(void);
t_time		ft_copy_time(const t_time	*src);

//		utilities.c
void		ft_smart_free(void	**memory);
bool		ft_smart_sleep(t_main	*env, size_t sleep_milliseconds);

//		utilities_queue.c
void		ft_my_push(t_queue	**queue, size_t philo_id);
size_t		ft_my_top(t_queue	**queue);
bool		ft_my_empty(t_queue	**queue);

//			print.c
void		ft_print_info(t_main	*env, const char	*event,
				const char	*color);
void		ft_print_died(t_main	*env);

//			debug.c
void		print_philos(const t_philo	*philos, size_t	count);
void		print_settings(const t_settings	*settings);
void		print_main(const t_main	*main);

//			utilities_int.c
int			ft_isdigit(int symbol);
int			ft_atoi(const char	*str);

//			utilities_string.c
size_t		ft_strlen(const char	*str);
int			ft_strncmp(const char	*str1, const char	*str2, size_t n);

//			exit.c
void		ft_fail(t_main	*env, const char	*message_error,
				bool is_clean);
void		ft_success(t_main	*env);

//			fill.c
bool		ft_fill(t_main	**main, t_settings	*settings);

//			initial.c
void		ft_initial_env(t_main	*env);

//			deinitial.c
void		ft_smart_free(void	**memory);
void		ft_deinitial_all(t_main	*_main);

//			action.c
void		*main_action(void	*data);

//			validation.c
bool		ft_read_args(t_settings	*settings, size_t argc, const char	**argv);

//			check.c
void		ft_check_result(t_main	*env, int code);

//			main.c
int			main(int argc, char	**argv);

#endif