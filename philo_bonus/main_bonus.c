/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:14:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/03 22:16:51 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <signal.h>

/*
idea[1] : Create thread (detached) from Child processes
		to monitoring him.
idea[2] : Create sem_stop inherate by all childs

*/
int		main(int ac, char *av[])
{
	int			i;
	data_t		data;
	philo_t		*philosopher;
	pid_t		*pid;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STOP);
	handling_args(&data, &pid, ac, av);
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
	sleep(2);
	i = -1;
	while (++i < data.num_ph)
		kill(pid[i], SIGINT);
	i = -1;
	while (++i < data.num_ph)
		waitpid(pid[i], NULL, 0);
	clean_all_resource(&data, &philosopher, &pid);
	return (0);
}
// sem = 0; if (sem == 1) do kill all process
