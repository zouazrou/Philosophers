/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:41:56 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:10:36 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_semaphores(t_data *data)
{
	int	i;

	data->forks = SEM_FAILED;
	data->kill = SEM_FAILED;
	data->write = SEM_FAILED;
	data->philos_done_eat = SEM_FAILED;
	i = -1;
	while (++i < data->num_ph)
		data->philosopher[i].sem_meal = SEM_FAILED;
}

void	open_semaphores(t_data *data)
{
	int		i;
	char	*name_sem;

	data->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, data->num_ph);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	data->kill = sem_open(SEM_KILL, O_CREAT, S_IRWXU, 0);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	data->write = sem_open(SEM_WRITE, O_CREAT, S_IRWXU, 1);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	data->philos_done_eat = sem_open(SEM_PH_COUNT, O_CREAT, S_IRWXU, 0);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	i = -1;
	while (++i < data->num_ph)
	{
		name_sem = generate_namesem(i);
		sem_unlink(name_sem);
		data->philosopher[i].sem_meal = sem_open(name_sem, O_CREAT, S_IRWXU, 1);
		free(name_sem);
		if (data->philosopher[i].sem_meal == SEM_FAILED)
			exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	}
}

void	close_semaphores(t_data *data)
{
	int	i;

	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->kill != SEM_FAILED)
		sem_close(data->kill);
	if (data->write != SEM_FAILED)
		sem_close(data->write);
	if (data->philos_done_eat != SEM_FAILED)
		sem_close(data->philos_done_eat);
	i = -1;
	while (++i < data->num_ph)
	{
		if (data->philosopher[i].sem_meal != SEM_FAILED)
			sem_close(data->philosopher[i].sem_meal);
	}
}

void	unlink_semaphore(t_data *data)
{
	int		i;
	char	*name_sem;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_KILL);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_PH_COUNT);
	i = -1;
	while (++i < data->num_ph)
	{
		name_sem = generate_namesem(i);
		if (!name_sem)
			exit((ft_putendl_fd("Error : malloc()", 2), EXIT_FAILURE));
		sem_unlink(name_sem);
		free(name_sem);
	}
}

char	*generate_namesem(int index)
{
	char	*num;
	char	*name;

	num = ft_itoa(index);
	if (!num)
		return (num);
	name = ft_strjoin(SEM_MEAL, num);
	free(num);
	return (name);
}
