/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 12:14:07 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"


/*
edge case :
*)t_sleep 0: (ODD NUM)
	-> if we not sleep some MSs some philos
	will wake up at the same time others put forks.
	that will cause to die one of philos

*/
void	thinking(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	// if (simulation_is_stop(data) == true)
		// return ;
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
	usleep(philo->data->t_eat * US);
	philo->num_meals++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
    return ;
}

void	*observer(void *arg)
{
	philo_t	*philo;

	philo = (philo_t *)arg;
	while (1)
	{
		if (is_die(philo) == true)
		{
			break;
		}
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
	// philo_t	*philo;

	// philo = (philo_t *)arg;
	// pthread_mutex_lock(philo->r_fork);
	// display("has taken a fork", philo);
	// usleep(philo->data->t_die * US);
	// pthread_mutex_unlock(philo->r_fork);
	// stop_simulation(philo->data);
	// display("died", philo);
	// return (NULL);
}
