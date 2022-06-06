#include "header.h"

void	ft_my_push(t_queue	**queue, size_t philo_id)
{
	ft_push(queue, (void *)&philo_id);
}

size_t	ft_my_top(t_queue	**queue)
{
	return (*(size_t *)ft_top((const t_queue **)queue));
}

bool	ft_my_empty(t_queue	**queue)
{
	return (ft_empty((const t_queue **)queue));
}
