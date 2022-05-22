#include "time.h"

t_u64int	GetDifferenceMs(const t_time	*time1, const t_time	*time2)
{
	//printf("Time 2: %ld,%ld\nTime 1: %ld,%ld\n\n", time2->tv_sec, time2->tv_usec, time1->tv_sec, time1->tv_usec);
	return ((t_u64int)(time2->tv_sec * 1000 + (time2->tv_usec / 1000))
			 - (t_u64int)(time1->tv_sec * 1000 + (time1->tv_usec / 1000)));
}

t_u64int	GetDifferenceCurrentTimeMs(const t_time	*time)
{
	t_time	time_current;

	gettimeofday(&time_current, NULL);
	return GetDifferenceMs(time, &time_current);
}

t_time GetCurrentTime()
{
	t_time	result;

	gettimeofday(&result, NULL);
	return (result);
}
