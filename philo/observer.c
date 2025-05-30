/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/29 11:04:33 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	display(char *str, philo_t *philo)
{
	data_t		*data;

	data = philo->data;

	pthread_mutex_lock(&data->display);
	if (simulation_is_stop(data) == false)
		printf("%lld %d %s\n", time_simulation(), philo->id, str);
	else if (simulation_is_stop(data) == true && *str == 'd')
		printf("%lld %d %s\n", time_simulation(), philo->id, str);
	pthread_mutex_unlock(&data->display);
}

bool	time_is_up(philo_t *philo)
{
	ms_t	curr;
	bool	val;

	curr = time_simulation();
	pthread_mutex_lock(&philo->meal_mutex);
	val = curr - philo->last_meal >= (philo->data->t_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (val);
}

bool	is_die(philo_t *philo)
{
	if (time_is_up(philo) == true)
	{
		stop_simulation(philo->data);
		display("died", philo);
		return (true);
	}
	return (false);
}

bool	valid_meals(philo_t *philo)
{
	int num_meals;

	num_meals = get_num_meals(philo);
	if (philo->num_meals >= philo->data->n_times_eat)
		return (true);
	return (false);
}

void	observer(data_t	*data)
{
	int		i;
	bool	n_times;

	while (simulation_is_stop(data) == false)
	{
		i = -1;
		n_times = true;
		while (++i < data->num_ph)
		{
			if (is_die(&data->philosopher[i]) == true)
			{
				break;
			}
			if (data->n_times_eat != UNAVAILABLE)
			{
				if (get_num_meals(&data->philosopher[i]) < data->n_times_eat)
					n_times = false;
			}
		}
		if (data->n_times_eat != UNAVAILABLE && n_times == true)
			stop_simulation(data);
	}
	return ;
}
