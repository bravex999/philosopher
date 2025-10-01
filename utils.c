/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chnaranj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:46:24 by chnaranj          #+#    #+#             */
/*   Updated: 2025/10/01 18:46:27 by chnaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error_inputs(char str, int flag_over);
static int	preprocess_head(char *str, int *i);
static int	loop_atoi_strong(char *str, long *acum, int *i);

int	ft_atoi_strong(char *str, long *out)
{
	int		i;
	long	acum;

	i = 0;
	acum = 0;
	if (preprocess_head(str, &i))
	{
		return (1);
	}
	if (loop_atoi_strong(str, &acum, &i))
	{
		return (1);
	}
	*out = acum;
	return (0);
}

static int	preprocess_head(char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
	{
		print_error_inputs(str[*i], 0);
		return (1);
	}
	if (str[*i] == '+')
	{
		if (str[*i + 1] >= '0' && str[*i + 1] <= '9')
			(*i)++;
		else
		{
			print_error_inputs(str[*i], 0);
			return (1);
		}
	}
	if (!(str[*i] >= '0' && str[*i] <= '9'))
	{
		print_error_inputs(str[*i], 0);
		return (1);
	}
	return (0);
}

static int	loop_atoi_strong(char *str, long *acum, int *i)
{
	int		digit;

	while (str[*i])
	{
		if (str[*i] >= '0' && str[*i] <= '9')
		{
			digit = str[*i] - '0';
			if (*acum > (INT_MAX - digit) / 10)
			{
				print_error_inputs(str[*i], 1);
				return (1);
			}
			*acum = *acum * 10 + digit;
			(*i)++;
		}
		else
		{
			print_error_inputs(str[*i], 0);
			return (1);
		}
	}
	return (0);
}

static void	print_error_inputs(char str, int flag_over)
{
	if (str == '-')
		printf("%s", "Error: Arguments must be positive integers\n");
	else if (!(str >= '0' && str <= '9'))
		printf("%s", "Error: Arguments must be integers\n");
	else if (flag_over == 1)
		printf ("%s", "Error: Value exceeds INT_MAX\n");
}

void	super_sleep(t_ms ms, t_shared *shared)
{
	t_ms	start;
	t_ms	now;
	int		stop_now;

	start = now_ms(shared);
	while (1)
	{
		pthread_mutex_lock(&shared->mutex_state);
		stop_now = shared->stop;
		pthread_mutex_unlock(&shared->mutex_state);
		if (stop_now)
			break ;
		now = now_ms(shared);
		if (now - start >= ms)
			break ;
		usleep(200);
	}
}
