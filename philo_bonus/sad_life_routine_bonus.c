/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad_life_routine_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:37:01 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/03 10:06:20 by zouazrou         ###   ########.fr       */
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
	// if (simulation_is_stop(philo->data) == true)
		// return ;
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * US);
}

void	eating(philo_t *philo)
{
	data_t	*data;

	data = philo->data;
	// if (simulation_is_stop(philo->data) == true)
	// 	return ;
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	display("is eating", philo);
	usleep(philo->data->t_eat * US);
	philo->last_meal = time_simulation(data);
	philo->num_meals++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
    return ;
}

/*
Idea 1: Once routine begin, Freeze odd/even Philosophers
		to avoiding deadlock
Idea 2: if (t_eat > t_sleep)
*/
void	philosopher_life(philo_t *philosopher)
{
	data_t	*data;
	int count = 10;


	data = philosopher->data;
	if (!(philosopher->id % 2))
		usleep(data->t_eat * US);
	while (count--)
	{
		// Eating
		eating(philosopher);

		// Sleeping
		sleeping(philosopher);

		// thinking
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
