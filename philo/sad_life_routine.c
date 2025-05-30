/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/30 23:25:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


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
	if (simulation_is_stop(data) == true)
		return ;
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
	if (simulation_is_stop(philo->data) == true)
		return ;
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * US);
}

void	eating(philo_t *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	display("is eating", philo);
	usleep(philo->data->t_eat * US);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time_simulation();
	philo->num_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
    return ;
}

void	use_left(philo_t *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	use_right(philo_t *philo)
{
	if (simulation_is_stop(philo->data) == true)
		return ;
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*
Idea 1: Once routine begin, Freeze odd/even Philosophers
		to avoiding deadlock
Idea 2: if (t_eat > t_sleep)
*/
void	*philosopher_life(void *arg)
{
	philo_t	*philo;

	philo = (philo_t *)arg;
	if (!(philo->id % 2))
		usleep(philo->data->t_eat * US);
	while (simulation_is_stop(philo->data) == false)
	{
		// Eating
		if ((philo->id % 2))
			use_right(philo);
		else
			use_left(philo);

		// Sleeping
		sleeping(philo);

		// thinking
		thinking(philo);
	}
	return (NULL);
}

void	*single_philosopher(void *arg)
{
	philo_t	*philo;

	philo = (philo_t *)arg;
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	usleep(philo->data->t_die * US);
	pthread_mutex_unlock(philo->r_fork);
	stop_simulation(philo->data);
	display("died", philo);
	return (NULL);
}
