/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:45:46 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:45:48 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include <pthread.h>

typedef struct s_philos	t_philos;

typedef long long		t_ms;

typedef struct s_config
{
	int	n;
	int	t_die_ms;
	int	t_eat_ms;
	int	t_sleep_ms;
	int	has_goal;
	int	must_eat;
}	t_config;

typedef enum e_log_kind
{
	LOG_TAKEN_FORK,
	LOG_EATING,
	LOG_SLEEPING,
	LOG_THINKING,
	LOG_DIED
}	t_log_kind;

typedef struct s_forks
{
	pthread_mutex_t	mtx;
	int				id;
}	t_forks;

typedef struct s_shared
{
	t_config		cfg;
	t_ms			t0_ms;
	int				stop;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_state;
	t_forks			*forks;
	t_philos		*philos;
}	t_shared;

struct s_philos
{
	int				id;
	int				meals;
	t_ms			last_meal_ms;
	pthread_t		thread;
	t_forks			*first;
	t_forks			*second;
	t_shared		*shared;
};

#endif
