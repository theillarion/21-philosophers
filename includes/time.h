#ifndef TIME_H
# define TIME_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct timeval t_time;
typedef unsigned long long t_u64int;

//			time.c
t_u64int	GetDifferenceMs(const struct timeval	*time1, const struct timeval	*time2);
t_u64int	GetDifferenceCurrentTimeMs(const t_time	*time);
t_time		GetCurrentTime();

#endif
