/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:45 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:01:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	display(char *str, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(philo->data->write);
	printf("%lld %d %s\n", time_simulation(data), philo->id, str);
	if (*str != 'd')
		sem_post(philo->data->write);
}

t_ms	time_simulation(t_data *data)
{
	t_ms	curr_time;

	curr_time = get_time();
	return (curr_time - data->start_time);
}

bool	valid_num_meals(t_philo *philosopher)
{
	if (fetch_num_meals(philosopher) >= philosopher->data->n_times_eat)
	{
		sem_post(philosopher->data->philos_done_eat);
		return (true);
	}
	return (false);
}

bool	is_die(t_philo *philo)
{
	if (time_simulation(philo->data)
		- fetch_last_meal(philo) >= philo->data->t_die)
	{
		display("died", philo);
		sem_post(philo->data->kill);
		return (true);
	}
	return (false);
}

void	*observer(void *arg)
{
	t_philo		*philo;
	static bool	valid_meals = false;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_die(philo) == true)
			break ;
		if (philo->data->n_times_eat != UNAVAILABLE && valid_meals == false)
			valid_meals = valid_num_meals(philo);
	}
	return (NULL);
}
