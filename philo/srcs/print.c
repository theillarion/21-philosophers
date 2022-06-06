#include "header.h"

#ifdef DEBUG_MODE

void	ft_print_info(t_main	*env, t_u64int time, size_t id, const char	*event,
	const char	*color)
{
	check(pthread_mutex_lock(&env->mutexes->print));
	printf("%s[%llu] #%zu %s\033[0m\n", color, time, id, event);
	check(pthread_mutex_unlock(&env->mutexes->print));
}

#else

void	ft_print_info(t_main	*env, t_u64int time, size_t id, const char	*event,
	const char	*color)
{
	(void)color;
	check(pthread_mutex_lock(&env->mutexes->print));
	printf("%llu %zu %s\n", time, id, event);
	check(pthread_mutex_unlock(&env->mutexes->print));
}

#endif
