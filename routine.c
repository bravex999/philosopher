/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:45:58 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:46:03 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	try_take_forks_help(t_philos *p)
{
	int	stop;

	pthread_mutex_lock(&p->shared->mutex_state);
	stop = p->shared->stop;
	pthread_mutex_unlock(&p->shared->mutex_state);
	if (stop)
	{
		pthread_mutex_unlock(&p->first->mtx);
		return (1);
	}
	if (!p->second)
	{
		pthread_mutex_unlock(&p->first->mtx);
		return (1);
	}
	pthread_mutex_lock(&p->second->mtx);
	print_event(p->shared, LOG_TAKEN_FORK, p->id);
	return (0);
}

static int	try_take_forks(t_philos *p)
{
	int	stop;

	pthread_mutex_lock(&p->shared->mutex_state);
	stop = p->shared->stop;
	pthread_mutex_unlock(&p->shared->mutex_state);
	if (stop)
		return (1);
	print_event(p->shared, LOG_THINKING, p->id);
	pthread_mutex_lock(&p->first->mtx);
	print_event(p->shared, LOG_TAKEN_FORK, p->id);
	return (try_take_forks_help(p));
}

static void	philo_routine_help(t_philos *p)
{
	t_ms	think;

	pthread_mutex_lock(&p->shared->mutex_state);
	p->last_meal_ms = now_ms(p->shared);
	p->meals++;
	pthread_mutex_unlock(&p->shared->mutex_state);
	print_event(p->shared, LOG_EATING, p->id);
	super_sleep(p->shared->cfg.t_eat_ms, p->shared);
	pthread_mutex_unlock(&p->first->mtx);
	pthread_mutex_unlock(&p->second->mtx);
	print_event(p->shared, LOG_SLEEPING, p->id);
	super_sleep(p->shared->cfg.t_sleep_ms, p->shared);
	if ((p->shared->cfg.n % 2) == 1)
	{
		think = p->shared->cfg.t_eat_ms - p->shared->cfg.t_sleep_ms;
		if (think < 1)
			think = 1;
		super_sleep(think, p->shared);
	}
	usleep(2000);
}

void	*philo_routine(void *arg)
{
	t_philos	*p;

	p = (t_philos *)arg;
	if ((p->id % 2) == 1)
		super_sleep(p->shared->cfg.t_eat_ms / 2, p->shared);
	while (1)
	{
		if (try_take_forks(p))
			break ;
		philo_routine_help(p);
	}
	return (NULL);
}
