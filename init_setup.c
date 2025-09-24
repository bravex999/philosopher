#include "philo.h"

int init_structs(t_shared *shared, t_config *config, int *temp)
{
	void(shared);

	config->n = temp[0];
	config->t_die_ms = temp[1];
	config->t_eat_ms = temp[2];
	config->t_sleep_ms = temp[3];
	if(temp[4])
		config->must_eat = temp[4];
}	




		




