/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/15 19:57:45 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	display(char *str, philo_t *philo)
{
	data_t		*data;
	static bool	one_isdie;

	data = philo->data;
	pthread_mutex_lock(&data->display);
	if (one_isdie == true)
	{
		pthread_mutex_unlock(&data->display);
		return ;
	}
	printf("%lld %d %s\n", time_simulation(), philo->id, str);
	if (*str == 'd')
		one_isdie = true;
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

ms_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit (2);
	return ((ms_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

ms_t	time_simulation(void)
{
	ms_t		curr_time;
	static ms_t	start_time;

	if (!start_time)
	{
		start_time = get_time();
		printf("simulation begin at %lld ms\n", start_time);
		return (0);
	}
	curr_time = get_time();
	return (curr_time - start_time);
}

void	clean_all_resource(data_t *data, pthread_t **ids)
{
	int	i;

	i = -1;
	// free array of id threads
	if (*ids)
	{
		free(*ids);
		*ids = NULL;
	}
	// destroy every mutex inside data_t struct and forks
	while (++i < data->num_ph)
	{
		pthread_mutex_destroy(&data->philosopher[i].meal_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		if (data->philosopher[i].l_fork)
			pthread_mutex_destroy(data->philosopher[i].l_fork);
		if (data->philosopher[i].r_fork)
			pthread_mutex_destroy(data->philosopher[i].r_fork);
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philosopher)
	{
		free(data->philosopher);
		data->philosopher = NULL;
	}
	pthread_mutex_destroy(&data->simulation_mutex);
}

bool	is_odd(int id)
{
	return (id % 2);
}
