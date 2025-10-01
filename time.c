/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:44:33 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:44:35 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_shared *shared)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	shared->t0_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

t_ms	now_ms(t_shared *shared)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((t_ms)(tv.tv_sec * 1000LL + tv.tv_usec / 1000) - shared->t0_ms);
}
