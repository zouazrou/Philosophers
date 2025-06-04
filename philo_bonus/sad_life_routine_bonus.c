/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 22:53:16 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	valid_num_meals(philo_t *philosopher)
{
	if (philosopher->num_meals >= philosopher->data->n_times_eat)
	{
		sem_post(philosopher->data->philos_are_full);
		return (true);
	}
	return (false);
}

void	thinking(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	display("is thinking", philo);
	if (data->t_eat >= data->t_sleep)
	{
		if (data->num_ph % 2) // ODD
			usleep(((data->t_eat * 2) - data->t_sleep) * US);
		else
			usleep((data->t_eat - data->t_sleep) * US);
	}
}

void	sleeping(philo_t *philo)
{
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * US);
}

void	eating(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	sem_wait(philo->data->forks);
	display("has taken a fork", philo);
	sem_wait(philo->data->forks);
	display("has taken a fork", philo);
	display("is eating", philo);
	philo->last_meal = time_simulation(data);
	philo->num_meals++;
	usleep(philo->data->t_eat * US);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
    return ;
}

void	*observer(void *arg)
{
	philo_t	*philo;
	static	bool valid_meals = false;

	philo = (philo_t *)arg;
	while (1)
	{
		if (is_die(philo) == true)
			break;
		if (philo->data->n_times_eat != UNAVAILABLE && valid_meals == false)
			valid_meals = valid_num_meals(philo);
	}
	return (NULL);
}

void	philosopher_life(philo_t *philosopher)
{
	pthread_t	th;

	pthread_create(&th, NULL, observer, philosopher);
	pthread_detach(th);
	if (!(philosopher->id % 2))
		usleep(philosopher->data->t_eat * US);
	while (true)
	{
		// Eating
		eating(philosopher);

		// Sleeping
		sleeping(philosopher);

		// Thinking
		thinking(philosopher);
	}
	exit (EXIT_SUCCESS);
}

void	single_philosopher(void)
{
	
}
