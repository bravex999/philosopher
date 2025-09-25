#include "philo.h"

#include "philo.h"

void	cleanup_shared(t_shared *shared)
{
	/*int	i;

	if (shared->forks)
	{
		i = 0;
		while (i < shared->cfg.n)
		{
			pthread_mutex_destroy(&shared->forks[i].mutex);
			i++;
		}
	}
	*/
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








