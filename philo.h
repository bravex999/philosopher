#ifndef PHILO_H
# define PHILO_H

# include "philo_types.h"
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

int		ft_atoi_strong(char *str, long *out);
int		init_structs(t_shared *shared, t_config *config, int *temp);
int		init_time(t_shared *shared);
t_ms	now_ms(t_shared *shared);
int		init_structs(t_shared *shared, t_config *config, int *temp);
int     init_mutexes(t_shared *shared);
int     setup_philos(t_shared *shared);
void    *philo_routine(void *arg);
int		start_threads(t_shared *shared);
void	*monitor_routine(void *arg);	
int		print_event(t_shared *shared, t_log_kind kind, int id);
void	cleanup_shared(t_shared *shared);
void    super_sleep(t_ms ms, t_shared *shared);

#endif
