/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 13:41:19 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_meal_completion(void *arg)
{
	data_t	*data;
	int 	num_philos;

	data = (data_t *)arg;
	num_philos = 0;
	while (num_philos < data->num_ph)
	{
		sem_wait(data->philos_done_eat);
		num_philos++;
	}
	sem_post(data->kill);
	return (NULL);
}

void	create_process(data_t *data)
{
	int			i;
	pthread_t	th;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_ph)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			exit((clean_all_resource(data, FORK), EXIT_FAILURE));
		if (data->pid[i] == 0)
			philosopher_life(data->philosopher + i);
	}
	if (data->n_times_eat != UNAVAILABLE)
	{
		pthread_create(&th, NULL, check_meal_completion, &data);
		pthread_detach(th);
	}
}

int		main(int ac, char *av[])
{
	data_t		data;

	handling_args(&data, ac, av);
	unlink_semaphore(&data);
	allocate_initial(&data);
	create_process(&data);
	sem_wait(data.kill);
	kill_process(&data);
	clean_all_resource(&data, NO_ERR);
	return (EXIT_SUCCESS);
}
