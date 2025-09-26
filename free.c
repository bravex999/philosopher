#include "philo.h"

void	cleanup_shared(t_shared *shared)
{
	int	i;

	if (shared->forks)
	{
		i = 0;
		while (i < shared->cfg.n)
		{
			pthread_mutex_destroy(&shared->forks[i].mtx);
			i++;
		}
	}
	pthread_mutex_destroy(&shared->mutex_state);
	pthread_mutex_destroy(&shared->mutex_print);
	if (shared->philos)
	{
		free(shared->philos);
		shared->philos = NULL;
	}
	if (shared->forks)
	{
		free(shared->forks);
		shared->forks = NULL;
	}
}
