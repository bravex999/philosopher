/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:45:09 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:45:11 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	signal_stop(t_shared *s);
static void	join_created(t_shared *s, int count);
static int	create_philos(t_shared *s);

int	start_threads(t_shared *shared)
{
	pthread_t	monitor;

	if (create_philos(shared) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine,
			(void *)shared) != 0)
	{
		signal_stop(shared);
		join_created(shared, shared->cfg.n);
		return (1);
	}
	pthread_join(monitor, NULL);
	join_created(shared, shared->cfg.n);
	return (0);
}

static void	signal_stop(t_shared *s)
{
	pthread_mutex_lock(&s->mutex_state);
	s->stop = 1;
	pthread_mutex_unlock(&s->mutex_state);
}

static void	join_created(t_shared *s, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		pthread_join(s->philos[i].thread, NULL);
		i++;
	}
}

static int	create_philos(t_shared *s)
{
	int		i;
	int		n;

	i = 0;
	n = s->cfg.n;
	while (i < n)
	{
		if (pthread_create(&s->philos[i].thread, NULL,
				philo_routine, (void *)&s->philos[i]) != 0)
		{
			signal_stop(s);
			join_created(s, i);
			return (1);
		}
		i++;
	}
	return (0);
}
