/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/04/15 09:13:39 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	handling_args(data_t *data, pthread_t **th_ids, int ac, char **av)
{
	// 5 or 6 (with optional arg)
    if (ac != 5 && ac != 6)
	{
        exit ((write(2, "Error : number of argments must 5 or 6\n", 40), 1));
	}
	memset(data, 0, sizeof(data_t));
	data->num_ph = ft_atoi_plus(av[1]);
    data->t_die = ft_atoi_plus(av[2]);
    data->t_eat = ft_atoi_plus(av[3]);
    data->t_sleep = ft_atoi_plus(av[4]);
    data->num_meals = UNAVAILABLE;
	if (ac == 6)
		data->num_meals = ft_atoi_plus(av[5]);
	*th_ids = malloc(data->num_ph * sizeof(pthread_t *));
	if (!*th_ids)
		exit((write(2, "Error : malloc\n", 16), 1));
	// memset(*th_ids, 0, data->num_ph * sizeof(pthread_t *));
}

void	allocate_initial(data_t *data)
{
	int	i;

	// allocation memory
	data->philosopher = malloc(data->num_ph * sizeof(philo_t));
	data->forks = 		malloc(data->num_ph * sizeof(pthread_mutex_t));
	if (!data->philosopher || !data->forks)
		exit((write(2, "Error : malloc\n", 16), 1)); // free all *

	// initualazation struct
	data->simulation = false;
	pthread_mutex_init(&data->simulation_mutex, NULL);
	pthread_mutex_init(&data->display, NULL);

	// initualize philo_t struct
	i = -1;
	while (++i < data->num_ph)
    {
		memset(data->philosopher + i, 0, sizeof(philo_t));
        pthread_mutex_init(&data->forks[i], NULL);
		data->philosopher[i].r_fork = &data->forks[(i+1) % data->num_ph];
		data->philosopher[i].l_fork = &data->forks[i % data->num_ph];
		data->philosopher[i].id = i + 1;
		data->philosopher[i].data = data;
		data->philosopher[i].last_meal = 0;
        pthread_mutex_init(&data->philosopher[i].meal_mutex, NULL);
		// printf("ph [%d] l = %d\n", data->philosopher[i].id, i %  data->num_ph);
		// printf("ph [%d] r = %d\n", data->philosopher[i].id, (i+1) % data->num_ph);
	}
}
