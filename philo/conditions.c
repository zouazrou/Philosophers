/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:24:00 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/29 10:57:31 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	simulation_is_stop(data_t *data)
{
	bool	val;
	pthread_mutex_lock(&data->simulation_mutex);
	val = data->simulation;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (val);
}

void	stop_simulation(data_t *data)
{
	pthread_mutex_lock(&data->simulation_mutex);
		data->simulation = true;
	pthread_mutex_unlock(&data->simulation_mutex);
}

int get_num_meals(philo_t *philo)
{
	int	val;

	pthread_mutex_lock(&philo->meal_mutex);
	val = philo->num_meals;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (val);
}
