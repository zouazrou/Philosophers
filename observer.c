/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/14 15:00:37 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	observer(data_t	*data)
{
	int	i;

	pthread_mutex_lock(&data->simulation_mutex);
	while (!data->simulation_stop)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		i = -1;
		while (++i < data->num_ph)
		{
			pthread_mutex_lock(&data->ph[i].meal_mutex);
			printf("%lld\n", get_time_difference(data) - data->ph[i].last_meal);
			if (get_time_difference(data) - data->ph[i].last_meal > (data->t_die))
			{
				// printf("%lld , %lld", get_time_difference(data) , data->t_die);
				pthread_mutex_unlock(&data->ph[i].meal_mutex);
				pthread_mutex_lock(&data->simulation_mutex);
				data->simulation_stop = true;
				pthread_mutex_unlock(&data->simulation_mutex);
				display("is die", &data->ph[i]);
				break;
			}
			pthread_mutex_unlock(&data->ph[i].meal_mutex);
		}
		pthread_mutex_lock(&data->simulation_mutex);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	return ;
}
