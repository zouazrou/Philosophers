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
	display("is thinking", philo);

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

void	use_left_hand_first(philo_t *philo)
{
	usleep(100);
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	sleeping(philo);
}

void	use_right_hand_first(philo_t *philo)
{
	pthread_mutex_lock(philo->r_fork);
	display("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	display("has taken a fork", philo);
	eating(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	sleeping(philo);
}

// 1 2 3 4 5
void    *philosopher_life(void *arg)
{
	philo_t	*philo;

	philo = (philo_t *)arg;
	display("is thinking", philo);
	pthread_mutex_lock(&philo->data->simulation_mutex);
	while (philo->data->simulation_stop == false)
	{
		pthread_mutex_unlock(&philo->data->simulation_mutex);
		if (is_odd(philo->id))
			use_right_hand_first(philo);
		else
			use_left_hand_first(philo);
		pthread_mutex_lock(&philo->data->simulation_mutex);
	}
	pthread_mutex_unlock(&philo->data->simulation_mutex);
	return (NULL);
}

int	main(int ac, char *av[])
{
	data_t	data;
	int		i;

	handling_input(&data, ac, av);
	init_arg(&data);
	i = -1;
	time_simulation();
	while (++i < data.num_ph)
		pthread_create(&data.ph[i].th, NULL, philosopher_life, &data.ph[i]);
	i = -1;
	observer(&data);
	while (++i < data.num_ph)
		pthread_join(data.ph[i].th, NULL);
	clean_all_resource(&data);
	return (0);
}
// 0 - 0 = 0 > 200
