/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:43:36 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:43:37 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_dead(t_shared *shared, int *who);
static int	all_done(t_shared *shared);
static int	read_stop(t_shared *shared);
static void	set_stop(t_shared *shared);

void	*monitor_routine(void *arg)
{
	t_shared	*shared;
	int			dead_id;

	shared = (t_shared *)arg;
	while (!read_stop(shared))
	{
		if (find_dead(shared, &dead_id))
		{
			print_event(shared, LOG_DIED, dead_id);
			break ;
		}
		if (all_done(shared))
		{
			set_stop(shared);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}

static int	read_stop(t_shared *shared)
{
	int	stop;

	pthread_mutex_lock(&shared->mutex_state);
	stop = shared->stop;
	pthread_mutex_unlock(&shared->mutex_state);
	return (stop);
}

static void	set_stop(t_shared *shared)
{
	pthread_mutex_lock(&shared->mutex_state);
	shared->stop = 1;
	pthread_mutex_unlock(&shared->mutex_state);
}

static int	find_dead(t_shared *shared, int *who)
{
	int		i;
	t_ms	now;
	t_ms	last;

	i = 0;
	while (i < shared->cfg.n)
	{
		pthread_mutex_lock(&shared->mutex_state);
		last = shared->philos[i].last_meal_ms;
		now = now_ms(shared);
		if (now - last > shared->cfg.t_die_ms)
		{
			*who = i;
			pthread_mutex_unlock(&shared->mutex_state);
			return (1);
		}
		pthread_mutex_unlock(&shared->mutex_state);
		i++;
	}
	return (0);
}

static int	all_done(t_shared *shared)
{
	int	i;
	int	done;

	if (shared->cfg.has_goal == 0)
		return (0);
	i = 0;
	done = 1;
	while (i < shared->cfg.n)
	{
		pthread_mutex_lock(&shared->mutex_state);
		if (shared->philos[i].meals < shared->cfg.must_eat)
			done = 0;
		pthread_mutex_unlock(&shared->mutex_state);
		if (!done)
			break ;
		i++;
	}
	return (done);
}
