#include "philo.h"

static void	print_number_args_error(void);
static int parameters_converter(char **argv, int i, long out);

int	main(int argc, char **argv)
{
	int		i;
	long	out;

	i = 1;
	out = 0;
	if (argc != 5 && argc != 6)
	{
		print_number_args_error();
		return (1);
	}
	if(parameters_converter(argv, i, out) == 1)
		return (1);
	return (0);
}

static int parameters_converter(char **argv, int i, long out)
{
	while (argv[i])
	{
		if (ft_atoi_strong(argv[i], &out) != 0)
			return (1);
		if (out == 0 && i == 1)
		{
			write(2, "Error: number_of_philosophers must be >= 1\n", 43);
			return (1);
		}
		if (out == 0 && (i >= 2 && i <= 5))
		{
			write(2, "Error: the value must be >= 1\n", 30);
			return (1);	
		}
		i++;
	}
	return (0);
}

static void	print_number_args_error(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
		sizeof ("Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n") - 1);
}
