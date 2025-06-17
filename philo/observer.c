/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 10:40:54 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	time_is_up(t_philo *philo)
{
	t_ms	curr;
	bool	val;

	curr = time_simulation();
	pthread_mutex_lock(&philo->meal_mutex);
	val = curr - philo->last_meal >= (philo->data->t_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (val);
}

bool	is_die(t_philo *philo)
{
	if (time_is_up(philo) == true)
	{
		stop_simulation(philo->data);
		display("died", philo);
		return (true);
	}
	return (false);
}

bool	valid_meals(t_philo *philo)
{
	int	num_meals;

	num_meals = get_num_meals(philo);
	if (philo->num_meals >= philo->data->n_times_eat)
		return (true);
	return (false);
}

void	observer(t_data *data)
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
				break ;
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
