#ifndef TIME_H
# define TIME_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct timeval t_time;
typedef unsigned long long t_u64int;

//			time.c
t_u64int	ft_get_difference_time_ms(const struct timeval	*time1, const struct timeval	*time2);
t_u64int	ft_get_difference_time_now_ms(const t_time	*time);
t_time		ft_get_now_time();
t_time		ft_copy_time(const t_time	*src);

#endif
