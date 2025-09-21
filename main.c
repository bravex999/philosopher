#include "philo.h"

int main (int argc, char **argv)
{
	(void)argv;

	if(argc != 4 && argc != 5)
	{
		printf("%s","Usage: ./philo "
		"number_of_philosophers time_to_die time_to_eat"
		" time_to_sleep optional:"
		"[number_of_times_each_philosopher_must_eat] \n");
		return (1);
	}
	return (0);
}
