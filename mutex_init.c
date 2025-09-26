#include "philo.h"

static void	destroy_forks(t_shared *shared, int limit);

int	init_mutexes(t_shared *shared)
{
	int	i;

	if (pthread_mutex_init(&shared->mutex_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared->mutex_state, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->mutex_print);
		return (1);
	}
	i = 0;
	while (i < shared->cfg.n)
	{
		if (pthread_mutex_init(&shared->forks[i].mtx, NULL) != 0)
		{
			destroy_forks(shared, i);
			pthread_mutex_destroy(&shared->mutex_state);
			pthread_mutex_destroy(&shared->mutex_print);
			return (1);
		}
		shared->forks[i].id = i;
		i++;
	}
	return (0);
}

static void	destroy_forks(t_shared *shared, int limit)
{
	int	j;

	j = 0;
	while (j < limit)
	{
		pthread_mutex_destroy(&shared->forks[j].mtx);
		j++;
	}
}
