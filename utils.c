#include "philo.h"

static void  print_error_inputs(char str)
{
	
	if(str == '-')
		printf("%s", "Error: Arguments must be positive integers\n");
	else if(!(str >= '0' && str <= '9'))
		printf("%s", "Error: Arguments must be integers\n");
		
}		
		
int ft_atoi_strong(char *str, long *out)
{
	int	i;
	long acum;
	
	i =		0;
	acum =	0;
	while(str[i] == ' ')
		i++;
	if(str[i] == '-')
	{
		print_error_inputs(str[i]);
		return (1);
	}	
	while(str[i])
	{
		if(str[i] == '+' && (!(str[i + 1] >= '0' && str[i + 1] <= '9')))
		{
			print_error_inputs(str[i]);
			return (1);
		}			
		if(str[i] == '+')
			i++;
		if(str[i] >= '0' && str[i] <= '9')
		{
			acum = acum * 10 + (str[i] - '0');
			i++;
		}	
		else if (!(str[i] >= '0' && str[i] <= '9'))
		{
			print_error_inputs(str[i]);			
			return (1);
		}
	}
	*out = acum;
	return (0);
}

int main (void)
{
	char *str;
	long result;

	str = "++999";
	if (ft_atoi_strong(str, &result) != 0)
		return (1);
	printf("%ld""%c", result, '\n');
	return 0;
}
