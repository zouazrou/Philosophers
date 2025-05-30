/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/30 23:12:13 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	handling_args(data_t *data, pthread_t **th_ids, int ac, char **av)
{
    if (ac != 5 && ac != 6)
	{
        exit((ft_putendl_fd("Error : number of argments must 5 or 6", 2), 1));
	}
	// memset(data, 0, sizeof(data_t));
	data->num_ph = ft_atoi_plus(av[1]);
    data->t_die = ft_atoi_plus(av[2]);
    data->t_eat = ft_atoi_plus(av[3]);
    data->t_sleep = ft_atoi_plus(av[4]);
    data->n_times_eat = UNAVAILABLE;
	if (ac == 6)
		data->n_times_eat = ft_atoi_plus(av[5]);
	if (!data->num_ph || !data->n_times_eat)
		exit(0);
	*th_ids = malloc(data->num_ph * sizeof(pthread_t));
	if (!*th_ids)
		exit((ft_putendl_fd("Error : malloc", 2), 1));
}

void	allocate_initial(data_t *data)
{
	int	i;

	// fprintf(stderr, "allocate_initial\n");
	// allocation memory
	data->philosopher = malloc(data->num_ph * sizeof(philo_t));
	data->forks = 		malloc(data->num_ph * sizeof(pthread_mutex_t));
	if (!data->philosopher || !data->forks)
		exit((ft_putendl_fd("Error : malloc", 2), 1)); // free all *

	// initualazation struct
	data->simulation = false;
	pthread_mutex_init(&data->simulation_mutex, NULL); // (2)
	pthread_mutex_init(&data->display, NULL); // (4)

	i = -1;
	while (++i < data->num_ph)
    {
        if (pthread_mutex_init(data->forks+i, NULL))
			printf("Error init 1\n");
        if (pthread_mutex_init(&(data->philosopher + i)->meal_mutex, NULL))
			printf("Error init 2\n");
	}

	i = -1;
	while (++i < data->num_ph)
    {
		data->philosopher[i].r_fork = &data->forks[(i+1) % data->num_ph];
		data->philosopher[i].l_fork = &data->forks[i % data->num_ph];
		data->philosopher[i].id = i + 1;
		data->philosopher[i].data = data;
		data->philosopher[i].num_meals = 0;
		data->philosopher[i].last_meal = 0;
	}
}
