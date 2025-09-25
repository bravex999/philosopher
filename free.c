#include "philo.h"

void free_philos(t_shared *shared->philos)
{
	int i;
	
	i = 0;
	while(shared->philos[i])
	{
		free(shared->philos[i])
		i++;
	}
}







