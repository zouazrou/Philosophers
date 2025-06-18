/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:06:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	display("is thinking", philo);
	if (data->t_eat >= data->t_sleep)
	{
		if (data->num_ph % 2)
			usleep(((data->t_eat * 2) - data->t_sleep) * US);
		else
			usleep((data->t_eat - data->t_sleep) * US);
	}
}

void	sleeping(t_philo *philo)
{
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * US);
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(philo->data->forks);
	display("has taken a fork", philo);
	sem_wait(philo->data->forks);
	display("has taken a fork", philo);
	display("is eating", philo);
	sem_wait(philo->sem_meal);
	philo->last_meal = time_simulation(data);
	philo->num_meals++;
	sem_post(philo->sem_meal);
	usleep(philo->data->t_eat * US);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return ;
}

void	philosopher_life(t_philo *philosopher)
{
	pthread_t	th;

	pthread_create(&th, NULL, observer, philosopher);
	pthread_detach(th);
	if (!(philosopher->id % 2))
		usleep(philosopher->data->t_eat * US);
	while (true)
	{
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	exit(EXIT_SUCCESS);
}
