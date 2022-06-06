#include "time.h"

t_u64int	ft_get_difference_time_ms(const t_time	*time1, const t_time	*time2)
{
	return ((t_u64int)(time2->tv_sec * 1000 + (time2->tv_usec / 1000))
			 - (t_u64int)(time1->tv_sec * 1000 + (time1->tv_usec / 1000)));
}

t_u64int	ft_get_difference_time_now_ms(const t_time	*time)
{
	t_time	time_current;

	gettimeofday(&time_current, NULL);
	return ft_get_difference_time_ms(time, &time_current);
}

t_time ft_get_now_time()
{
	t_time	result;

	gettimeofday(&result, NULL);
	return (result);
}

t_time	ft_copy_time(const t_time	*src)
{
	t_time	result;

	result.tv_sec = 0;
	result.tv_usec = 0;
	if (src == NULL)
		return (result);
	result.tv_sec = src->tv_sec;
	result.tv_usec = src->tv_usec;
	return (result);
}
