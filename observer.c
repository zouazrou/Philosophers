/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/15 20:01:03 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

bool	is_die(philo_t *philo)
{
	bool	s;
	ms_t	curr;

	curr = time_simulation();
	// printf("----------\n");
	// printf("-->curr = %lld\n", curr);
	pthread_mutex_lock(&philo->meal_mutex);
	s = (curr - philo->last_meal >= (philo->data->t_die));
	pthread_mutex_unlock(&philo->meal_mutex);
	// printf("curr = %lld\n", curr - philo->last_meal >= (philo->data->t_die));
	return (s);
}

void	observer(data_t	*data)
{
	int	i;

	while (simulation_stop(data) == false)
	{
		i = -1;
		while (++i < data->num_ph)
		{
			if (is_die(&data->philosopher[i]))
			{
				pthread_mutex_lock(&data->simulation_mutex);
				data->simulation = true;
				pthread_mutex_unlock(&data->simulation_mutex);
				display("died", &data->philosopher[i]);
				break ;
			}
		}
	}
	return ;
}
