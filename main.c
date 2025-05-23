/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/17 17:37:33 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


void	sleeping(philo_t *philo)
{
	display("is sleeping", philo);
	usleep(philo->data->t_sleep * MS);
}

// void    sleeping(data_t *data, int id)
// {
//     printf("%ld %d is sleeping\n", get_time_difference(data), id+1);
//     usleep(data->t_sleep);
//     thinking(data, id);
// }

int    eating(philo_t *philo)
{
	// static bool	first = true;
	// int			r;

	display("is eating", philo);
	usleep(philo->data->t_eat * MS);
	philo->last_meal = time_simulation();
    return (0);
}

void	use_left(philo_t *philo)
{
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
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

//
void    *philosopher_life(void *arg)
{
	philo_t	*philo;

	philo = (philo_t *)arg;
	// display("is thinking", philo);
	while (simulation_stop(philo->data) == false)
	{
		// Eating
		if (IS_ODD(philo->id))
			use_right(philo);
		else
			use_left(philo);

		// Sleeping
		sleeping(philo);

		// thinking
		display("is thinking", philo);
	}
	return (NULL);
}

int		main(int ac, char *av[])
{
	int			i;
	data_t		data;
	pthread_t	*thread_ids;

	handling_args(&data, &thread_ids, ac, av);
		fprintf(stderr, "handling_args\n");
	allocate_initial(&data);
		fprintf(stderr, "allocate_initial\n");
	i = -1;
	time_simulation();
	while (++i < data.num_ph)
	{
		pthread_create(thread_ids + i, NULL, philosopher_life, &data.philosopher[i]);
	}
	// observer(&data);
	i = -1;
	while (++i < data.num_ph)
		pthread_join(thread_ids[i], NULL);
	clean_all_resource(&data, &thread_ids);
		fprintf(stderr, "clean all resource\n");
	return (0);
}
// 0 - 0 = 0 > 200
