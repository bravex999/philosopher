/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:42:45 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:42:47 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_shared(t_shared *shared)
{
	int	i;

	if (shared->forks)
	{
		i = 0;
		while (i < shared->cfg.n)
		{
			pthread_mutex_destroy(&shared->forks[i].mtx);
			i++;
		}
	}
	pthread_mutex_destroy(&shared->mutex_state);
	pthread_mutex_destroy(&shared->mutex_print);
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
