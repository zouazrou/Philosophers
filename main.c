/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/14 15:20:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


void	sleeping(philo_t *philo)
{
	display("is sleeping", philo);
	usleep(((data_t *)philo->data)->t_sleep);
	display("is thinking", philo);

}

// void    sleeping(data_t *data, int id)
// {
//     printf("%ld %d is sleeping\n", get_time_difference(data), id+1);
//     usleep(data->t_sleep);
//     thinking(data, id);
// }

int    eating(philo_t *philo)
{
	// static bool	first = true;
	// int			r;

	display("is eating", philo);
	usleep(((data_t *)philo->data)->t_eat);
	philo->last_meal = get_current_time();
    return (0);
}

void    *philosopher_life(void *arg)
{
	philo_t	*philo;
	data_t	*data;

	philo = (philo_t *)arg;
	data = (data_t *)philo->data;
	display("is thinking", philo);
	// printf("%d\n", philo->id);
	pthread_mutex_lock(&data->simulation_mutex);
	while (data->simulation_stop == false)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		if (!is_odd(philo->id))
		{
			pthread_mutex_lock(philo->l_fork);
			display("has taken a fork", philo);
			pthread_mutex_lock(philo->r_fork);
			display("has taken a fork", philo);
			eating(philo);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			sleeping(philo);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			display("has taken a fork", philo);
			pthread_mutex_lock(philo->l_fork);
			display("has taken a fork", philo);
			eating(philo);
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			sleeping(philo);
		}
		// th(1): lock(l) -> print -> lock(r) -> print -> unlock(l) -> unlock (r) -> lock(l)
		// th(2): lock(l) -> block    block      block -> lock(l)  ->print -> lock(r) -> print -> unlock(l) -> unlock (r)
		pthread_mutex_lock(&data->simulation_mutex);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	return (NULL);
}

int	main(int ac, char *av[])
{
	data_t	data;
	int		i;

	handling_input(&data, ac, av);
	init_arg(&data);
	i = -1;
	// printf("time before create threads -> %lld-%lld\n", get_current_time() - data.start_time, get_current_time());
	data.start_time = get_current_time();
	while (++i < data.num_ph)
	{
		pthread_create(&data.ph[i].th, NULL, philosopher_life, &data.ph[i]);
	}
	i = -1;
	// usleep(5000);
	// pthread_mutex_lock(&data.simulation_mutex);
	// data.simulation_stop = true;
	// pthread_mutex_unlock(&data.simulation_mutex);
		// observer(&data);

	while (++i < data.num_ph)
	{
		pthread_join(data.ph[i].th, NULL);
	}
	clean_all_resource(&data);
    return (0);
}
// 0 - 0 = 0 > 200
