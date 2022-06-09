#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include "../lib/queue/includes/queue.h"

typedef struct timeval		t_time;
typedef unsigned long long	t_u64int;

typedef struct s_philo
{
	short	id;
	short	left_fork;
	short	right_fork;
	t_time	time_last_eat;
	size_t	count_iteration;
	bool	is_infinity;
}			t_philo;

typedef struct s_settings
{
	t_time		start_time;
	short		count_philo;
	t_u64int	time_to_die;
	t_u64int	time_to_eat;
	t_u64int	time_to_sleep;
	size_t		count_eat;
	bool		is_end;
}			t_settings;

typedef struct s_status
{
	bool			is_die;
	short			id;
}					t_status_death;

typedef struct s_mutexes
{
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
}					t_mutexes;

typedef struct s_environment
{
	t_philo			*adrs_philo;
	pthread_t		*adrs_threads;
	t_status_death	*status_death;
	t_settings		*settings;
	t_mutexes		*mutexes;
}					t_environment;

//			action_death.c
bool		ft_death(t_environment	*env);
bool		ft_is_died(t_environment	*env, pthread_mutex_t	*mutex1,
				pthread_mutex_t	*mutex2);

//			time.c
t_u64int	ft_get_difference_time_ms(const t_time	*time1,
				const t_time	*time2);
t_u64int	ft_get_difference_time_now_ms(const t_time	*time);
t_time		ft_get_now_time(void);
t_time		ft_copy_time(const t_time	*src);

//			utilities.c
void		ft_smart_free(void	**memory);
bool		ft_smart_sleep(t_environment	*env, size_t sleep_milliseconds);

//			print.c
void		ft_print_info(t_environment	*env, const char	*event,
				const char	*color);
void		ft_print_died(t_environment	*env);

//			utilities_int.c
int			ft_isdigit(int symbol);
int			ft_atoi(const char	*str);

//			utilities_string.c
size_t		ft_strlen(const char	*str);
int			ft_strncmp(const char	*str1, const char	*str2, size_t n);

//			exit.c
void		ft_fail(t_environment	*env, const char	*message_error,
				bool is_clean);
void		ft_success(t_environment	*env);

//			fill.c
bool		ft_fill(t_environment	**main, t_settings	*settings);

//			initial.c
void		ft_initial_env(t_environment	*env);

//			deinitial.c
void		ft_smart_free(void	**memory);
void		ft_deinitial_all(t_environment	*_main);

//			action.c
void		*ft_main_action(void	*data);

//			validation.c
bool		ft_read_args(t_settings	*settings, size_t argc, const char	**argv);

//			check.c
void		ft_check_result(t_environment	*env, int code);

//			main.c
int			main(int argc, char	**argv);

#endif