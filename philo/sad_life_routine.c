/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 10:40:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
edge case :
*)t_sleep 0: (ODD NUM)
	-> if we not sleep some MSs some philos
	will wake up at the same time others put forks.
	that will cause to die one of philos

*/
void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (simulation_is_stop(data) == true)
		return ;
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
	if (simulation_is_stop(philo->data) == true)
		return ;
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * US);
}

void	eating(t_philo *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	display("is eating", philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time_simulation();
	philo->num_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->t_eat * US);
	return ;
}

/*
Idea 1: Once routine begin, Freeze odd/even Philosophers
		to avoiding deadlock
Idea 2: if (t_eat > t_sleep)
*/
void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(philo->data->t_eat * US);
	while (simulation_is_stop(philo->data) == false)
	{
		if ((philo->id % 2))
			use_right(philo);
		else
			use_left(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*single_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	usleep(philo->data->t_die * US);
	pthread_mutex_unlock(philo->r_fork);
	stop_simulation(philo->data);
	display("died", philo);
	return (NULL);
}
