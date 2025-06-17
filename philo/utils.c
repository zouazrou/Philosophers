/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 10:34:15 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display(char *str, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->display);
	if (simulation_is_stop(data) == false)
		printf("%lld %d %s\n", time_simulation(), philo->id, str);
	else if (simulation_is_stop(data) == true && *str == 'd')
		printf("%lld %d %s\n", time_simulation(), philo->id, str);
	pthread_mutex_unlock(&data->display);
}

t_ms	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

t_ms	time_simulation(void)
{
	t_ms		curr_time;
	static t_ms	start_time;

	if (!start_time)
	{
		start_time = get_time();
		return (start_time);
	}
	curr_time = get_time();
	return (curr_time - start_time);
}

void	garbage_collector(t_data *data)
{
	if (data->addrs[0])
	{
		free(data->addrs[0]);
		data->addrs[0] = NULL;
	}
	if (data->addrs[1])
	{
		free(data->addrs[1]);
		data->addrs[1] = NULL;
	}
	if (data->addrs[2])
	{
		free(data->addrs[2]);
		data->addrs[2] = NULL;
	}
}

void	clean_all_resource(t_data *data, t_err err)
{
	int	i;

	if (err == ARG || err == EDGE)
		return ;
	if (err != MALLOC)
	{
		pthread_mutex_destroy(&data->simulation_mutex);
		pthread_mutex_destroy(&data->display);
		i = -1;
		while (++i < data->num_ph)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philosopher[i].meal_mutex);
		}
	}
	garbage_collector(data);
}
