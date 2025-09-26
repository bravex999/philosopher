#include "philo.h"

static void	print_number_args_error(void);
static int	aux_main(t_shared *shared);
static int	parameters_conv(char **argv, int i, long out, t_shared *shared);

int	main(int argc, char **argv)
{
	t_shared	shared;
	int			i;
	long		out;

	i = 1;
	out = 0;
	if (argc != 5 && argc != 6)
	{
		print_number_args_error();
		return (1);
	}
	if (parameters_conv(argv, i, out, &shared) == 1)
		return (1);
	if (aux_main(&shared) == 1)
		return (1);
	return (0);
}

static int	aux_main(t_shared *shared)
{
	if (init_mutexes(shared) == 1)
	{
		free(shared->philos);
		shared->philos = NULL;
		free(shared->forks);
		shared->forks = NULL;
		return (1);
	}
	if (init_time(shared) != 0)
	{
		write(2, "Error: tiempo base falló\n", 25);
		cleanup_shared(shared);
		return (1);
	}
	if (init_time(shared) != 0
		|| setup_philos(shared) != 0
		|| start_threads(shared) != 0)
	{
		cleanup_shared(shared);
		return (1);
	}
	cleanup_shared(shared);
	return (0);
}

static int	parameters_conv(char **argv, int i, long out, t_shared *shared)
{
	int			t_index;
	int			temp[5];
	t_config	config;

	t_index = 0;
	memset(temp, 0, sizeof(temp));
	while (argv[i])
	{
		if (ft_atoi_strong(argv[i], &out) != 0)
			return (1);
		if (out == 0 && (i >= 1 && i <= 5))
		{
			write(2, "Error: the value must be >= 1\n", 30);
			return (1);
		}
		temp[t_index++] = out;
		i++;
	}
	if (init_structs(shared, &config, temp) != 0)
		return (1);
	return (0);
}

static void	print_number_args_error(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
		sizeof ("Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n") - 1);
}
