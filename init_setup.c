#include "philo.h"

static int init_philo_shared(t_shared *shared, t_config *config);

int	init_structs(t_shared *shared, t_config *config, int *temp)
{
	int i;
	i = 0;

	memset(config, 0, sizeof(t_config));
	while (i <= 3)
	{
		if(temp[i] == 0)
			return (1);
		i++;		
	}			
	config->n = temp[0];
	config->t_die_ms = temp[1];
	config->t_eat_ms = temp[2];
	config->t_sleep_ms = temp[3];
	if(temp[4] != 0)
	{
		config->has_goal = 1;
		config->must_eat = temp[4];
	}
	if(init_philo_shared(shared, config) != 0)
		return (1);
	return(0);
}

static int init_philo_shared(t_shared *shared, t_config *config)	
{
	shared->philos = malloc(sizeof(t_philos) * config->n);
	if(!shared->philos)
		return (1);
	memset(shared->philos, 0, sizeof(t_philos) * config->n);
	shared->forks = malloc(sizeof(t_forks) * config->n);
	if(!shared->forks)
	{
		free(shared->philos);
		shared->philos= NULL;
		return (1);
	}
	memset(shared->forks, 0, sizeof(t_forks) * config->n);
	shared->cfg = *config;
	return (0);
}	




		




