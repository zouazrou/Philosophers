/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 22:51:51 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_philos_are_full(void *arg)
{
	data_t	*data;
	int 	num_philos;

	data = (data_t *)arg;
	num_philos = 0;
	while (num_philos < data->num_ph)
	{
		sem_wait(data->philos_are_full);
		num_philos++;
	}
	sem_post(data->kill);
	return (NULL);
}

int		main(int ac, char *av[])
{
	int			i;
	data_t		data;
	pthread_t	th;
	pid_t		*pid;
	philo_t		*philosopher;

	handling_args(&data, &pid, ac, av);
	unlink_semaphore(data.num_ph);
	allocate_initial(&philosopher, &data);

	i = -1;
	data.start_time = get_time();
	while (++i < data.num_ph)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit((ft_putendl_fd("error : main:32 fork()", STDERR_FILENO), EXIT_FAILURE));
		if (pid[i] == 0)
			philosopher_life(philosopher + i);
	}
	if (data.n_times_eat != UNAVAILABLE)
	{
		pthread_create(&th, NULL, check_philos_are_full, &data);
		pthread_detach(th);
	}
	sem_wait(data.kill);
	i = -1;
	while (++i < data.num_ph)
		kill(pid[i], SIGKILL);
	i = -1;
	while (++i < data.num_ph)
		waitpid(pid[i], NULL, 0);
	clean_all_resource(&data, &philosopher, &pid, data.num_ph);
	return (0);
}
