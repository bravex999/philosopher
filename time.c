#include "philo.h"

int	init_time(t_shared *shared)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	shared->t0_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}
