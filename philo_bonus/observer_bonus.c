/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 15:33:15 by zouazrou         ###   ########.fr       */
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

	if (time_simulation(philo->data) - fetch_last_meal(philo) >= philo->data->t_die)
	{
		display("died", philo);
		sem_post(philo->data->kill);
		return (true);
	}
	return (false);
}
