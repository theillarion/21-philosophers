#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <semaphore.h>

typedef struct timeval		t_time;
typedef unsigned long long	t_u64int;

typedef struct s_philo
{
	short	id;
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
}				t_settings;

typedef struct s_name_semaphores
{
	char	*print;
	char	*forks;
	char	*death;
}			t_name_semaphores;

typedef struct s_semaphores
{
	sem_t	*print;
	sem_t	*forks;
	sem_t	*death;
}			t_semaphores;

typedef struct s_environment
{
	pid_t				*pids;
	t_philo				*adrs_philo;
	t_settings			*settings;
	t_name_semaphores	*names_semaphores;
	t_semaphores		*semaphores;
}					t_environment;

//			semaphores.c
sem_t		*ft_open_semaphore(const char	*name, unsigned int value);
char		*ft_get_name_semaphore(const char	*name);
void		ft_wait(t_environment	*env);

//			action_death.c
void		ft_death(t_environment	*env);
bool		ft_is_died(t_environment	*env, sem_t	*semaphore1,
				sem_t	*semaphore2);

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
void		ft_print_died(t_environment	*env, short id);

//			utilities_int.c
int			ft_isdigit(int symbol);
int			ft_atoi(const char	*str);

//			utilities_int_2.c
char		*ft_itoa(int number);

//			utilities_string.c
size_t		ft_strlen(const char	*str);
int			ft_strncmp(const char	*str1, const char	*str2, size_t n);
char		*ft_strjoin(const char	*str1, const char	*str2);
char		*ft_strdup(const char	*str);

//			exit.c
void		ft_fail(t_environment	*env, const char	*message_error,
				bool is_clean);
void		ft_success(t_environment	*env);

//			fill.c
bool		ft_fill(t_environment	**main, t_settings	*settings);

//			initial.c
void		ft_initial_env(t_environment	*env);

//			deinitial.c
void		ft_deinitial_all(t_environment	*_main);

//			action.c
void		ft_main_action(t_environment	*env);

//			validation.c
bool		ft_read_args(t_settings	*settings, size_t argc, const char	**argv);

//			check.c
void		ft_check_result(t_environment	*env, int code);

//			main.c
int			main(int argc, char	**argv);

#endif