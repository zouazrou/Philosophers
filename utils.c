/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/14 14:15:58 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	display(char *str, philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	pthread_mutex_lock(&data->display);
	printf("%lld %d %s\n", get_time_difference(data), philo->id, str);
	pthread_mutex_unlock(&data->display);
}
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

long long	ft_atoi_plus(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	// while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
	// 	i++;

	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((write(2, "Error : time must be positive (-_-)\n", 37), 1));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((write(2, "Error : argument must be digit\n", 32), 1));
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb);
}

// to convert from s to ms : * 1000
// to convert from s to ms : / 1000
long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit (2);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

long long	get_time_difference(data_t *data)
{
	long long	curr;

	curr = get_current_time();
	return (curr - data->start_time);
}

void	clean_all_resource(data_t *data)
{
	int	i;

	i = -1;
	while (++i < data->num_ph)
	{
		pthread_mutex_destroy(&data->ph[i].meal_mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	free(data->forks);
	data->forks = NULL;
	free(data->ph);
	data->ph = NULL;
	pthread_mutex_destroy(&data->simulation_mutex);
}

bool	is_odd(int id)
{
	return (id % 2);
}
