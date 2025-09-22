#include "philo.h"

static void print_number_args_error(); 

int main (int argc, char **argv)
{
	(void)argv;

	if(argc != 5 && argc != 6)
	{
		print_number_args_error();
		return (1);
	}
	return (0);
}

static void print_number_args_error()
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
      "time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
      sizeof("Usage: ./philo number_of_philosophers time_to_die time_to_eat "
             "time_to_sleep [number_of_times_each_philosopher_must_eat]\n") - 1);

}	

