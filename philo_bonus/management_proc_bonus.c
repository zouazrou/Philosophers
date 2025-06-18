/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_proc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:50:23 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:01:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_meal_completion(void *arg)
{
	t_data	*data;
	int		num_philos;

	data = (t_data *)arg;
	num_philos = 0;
	while (num_philos < data->num_ph)
	{
		sem_wait(data->philos_done_eat);
		num_philos++;
	}
	sem_post(data->kill);
	return (NULL);
}

void	create_process(t_data *data)
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
		pthread_create(&th, NULL, check_meal_completion, data);
		pthread_detach(th);
	}
}

void	kill_process(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_ph)
	{
		if (data->pid[i] > 0)
			kill(data->pid[i], SIGKILL);
	}
	i = -1;
	while (++i < data->num_ph)
	{
		if (data->pid[i] > 0)
			waitpid(data->pid[i], NULL, 0);
	}
}
