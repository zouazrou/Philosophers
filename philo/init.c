/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/17 10:27:00 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handling_args(t_data *data, pthread_t **th_ids, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		return ((ft_putendl_fd("Error : number of argments must 5 or 6", 2),
				ARG));
	}
	data->num_ph = ft_atoi_plus(av[1]);
	data->t_die = ft_atoi_plus(av[2]);
	data->t_eat = ft_atoi_plus(av[3]);
	data->t_sleep = ft_atoi_plus(av[4]);
	data->n_times_eat = UNAVAILABLE;
	if (ac == 6)
		data->n_times_eat = ft_atoi_plus(av[5]);
	if (!data->num_ph || !data->n_times_eat)
		return (EDGE);
	*th_ids = malloc(data->num_ph * sizeof(pthread_t));
	data->addrs[0] = *th_ids;
	if (!*th_ids)
		return ((ft_putendl_fd("Error : malloc", 2), MALLOC));
	return (NO_ERR);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_ph)
	{
		data->philosopher[i].r_fork = &data->forks[(i + 1) % data->num_ph];
		data->philosopher[i].l_fork = &data->forks[i % data->num_ph];
		data->philosopher[i].id = i + 1;
		data->philosopher[i].data = data;
		data->philosopher[i].num_meals = 0;
		data->philosopher[i].last_meal = 0;
	}
}

int	allocate_initial(t_data *data)
{
	int	i;

	data->philosopher = malloc(data->num_ph * sizeof(t_philo));
	data->addrs[1] = data->philosopher;
	data->forks = malloc(data->num_ph * sizeof(pthread_mutex_t));
	data->addrs[2] = data->forks;
	if (!data->philosopher || !data->forks)
		return ((ft_putendl_fd("Error : malloc", 2), MALLOC));
	data->simulation = false;
	pthread_mutex_init(&data->simulation_mutex, NULL);
	pthread_mutex_init(&data->display, NULL);
	i = -1;
	while (++i < data->num_ph)
	{
		pthread_mutex_init(data->forks + i, NULL);
		pthread_mutex_init(&data->philosopher[i].meal_mutex, NULL);
	}
	init_philos(data);
	return (NO_ERR);
}
