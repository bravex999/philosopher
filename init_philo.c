#include "philo.h"

static void	assign_forks(t_shared *shared, t_philos *p, int i)
{
	int	n;
	int	der;

	n = shared->cfg.n;
	if (n == 1)
	{
		p->first = &shared->forks[i];
		p->second = NULL;
		return ;
	}
	der = (i + 1) % n;
	if (i < der)
	{
		p->first = &shared->forks[i];
		p->second = &shared->forks[der];
	}
	else
	{
		p->first = &shared->forks[der];
		p->second = &shared->forks[i];
	}
}

int	setup_philos(t_shared *shared)
{
	int			i;
	int			n;
	t_philos	*p;

	i = 0;
	n = shared->cfg.n;
	while (i < n)
	{
		p = &shared->philos[i];
		p->id = i;
		p->shared = shared;
		p->meals = 0;
		p->last_meal_ms = now_ms(shared);
		assign_forks(shared, p, i);
		i++;
	}
	return (0);
}
