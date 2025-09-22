#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include <pthread.h>

typedef struct s_philo	t_philo;

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

typedef struct s_fork
{
	pthread_mutex_t	mtx;
	int				id;
}	t_fork;

typedef struct s_shared
{
	t_config		cfg;
	t_ms			t0_ms;
	int				stop;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_state;
	t_fork			*forks;
	t_philo			*philos;
}	t_shared;

struct s_philo
{
	int				id;
	int				meals;
	t_ms			last_meal_ms;
	pthread_t		thread;
	t_fork			*first;
	t_fork			*second;
	t_shared		*shared;
};

#endif
