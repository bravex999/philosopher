#include "philo.h"

static const char	*event_text(t_log_kind kind)
{
	if (kind == LOG_TAKEN_FORK)
		return ("has taken a fork");
	if (kind == LOG_EATING)
		return ("is eating");
	if (kind == LOG_SLEEPING)
		return ("is sleeping");
	if (kind == LOG_THINKING)
		return ("is thinking");
	return ("died");
}

int	print_event(t_shared *shared, t_log_kind kind, int id)
{
	t_ms	ts;
	int		stop_now;

	pthread_mutex_lock(&shared->mutex_state);
	stop_now = shared->stop;
	if (kind == LOG_DIED)
		shared->stop = 1;
	pthread_mutex_unlock(&shared->mutex_state);
	ts = now_ms(shared);
	pthread_mutex_lock(&shared->mutex_print);
	pthread_mutex_lock(&shared->mutex_state);
	stop_now = shared->stop;
	pthread_mutex_unlock(&shared->mutex_state);
	if (stop_now && kind != LOG_DIED)
	{
		pthread_mutex_unlock(&shared->mutex_print);
		return (0);
	}
	printf("%lld %d %s\n", (long long)ts, id + 1, event_text(kind));
	pthread_mutex_unlock(&shared->mutex_print);
	return (0);
}
