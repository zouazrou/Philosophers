/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 11:40:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	display(char *str, philo_t *philo)
{
	data_t		*data;

	data = philo->data;

	sem_wait(philo->data->write);
	printf("%lld %d %s\n", time_simulation(data), philo->id, str);
	if (*str != 'd')
		sem_post(philo->data->write);
}
bool	is_die(philo_t *philo)
{
	if (time_simulation(philo->data) - philo->last_meal >= philo->data->t_die)
	{
		// decremante semaphore to block any process try to printf()
		sem_wait(philo->data->simulation_stop);
		display("died", philo);
		sem_post(philo->data->kill);
		return (true);
	}
	return (false);
}

bool	valid_meals(philo_t *philo)
{
	// int num_meals;
	(void)philo;

	// num_meals = get_num_meals(philo);
	// if (philo->num_meals >= philo->data->n_times_eat)
	// 	return (true);
	return (false);
}

// void	observer(data_t	*data)
// {
// 	int		i;
// 	bool	n_times;

// 	while (simulation_is_stop(data) == false)
// 	{
// 		i = -1;
// 		n_times = true;
// 		while (++i < data->num_ph)
// 		{
// 			if (is_die(&data->philosopher[i]) == true)
// 			{
// 				break;
// 			}
// 			if (data->n_times_eat != UNAVAILABLE)
// 			{
// 				if (get_num_meals(&data->philosopher[i]) < data->n_times_eat)
// 					n_times = false;
// 			}
// 		}
// 		if (data->n_times_eat != UNAVAILABLE && n_times == true)
// 			stop_simulation(data);
// 	}
// 	return ;
// }
