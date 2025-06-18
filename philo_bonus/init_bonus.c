/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 15:42:44 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	init_semaphores(data_t *data)
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

void	open_semaphores(data_t *data)
{
	int		i;
	char	*name_sem;
	/**********/
	data->forks = sem_open(SEM_FORKS, O_CREAT, S_IRUSR | S_IWUSR, data->num_ph);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	/**********/
	data->kill = sem_open(SEM_KILL, O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	/**********/
	data->write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	/**********/
	data->philos_done_eat = sem_open(SEM_PH_COUNT, O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (data->forks == SEM_FAILED)
		exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	/**********/
	i = -1;
	while (++i < data->num_ph)
	{
		name_sem = generate_namesem(i);
		sem_unlink(name_sem);
		data->philosopher[i].sem_meal = sem_open(name_sem, O_CREAT, S_IRUSR | S_IWUSR, 1);
		free(name_sem);
		if (data->philosopher[i].sem_meal == SEM_FAILED)
			exit((clean_all_resource(data, SEM_OPEN), EXIT_FAILURE));
	}
}

void	close_semaphores(data_t *data)
{
	int	i;

	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->kill != SEM_FAILED)
		sem_close(data->kill );
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

void		unlink_semaphore(data_t *data)
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

void	allocate_initial(data_t *data)
{
	int		i;

	i = -1;
	data->philosopher = malloc(data->num_ph * sizeof(philo_t));
	if (!data->philosopher)
		exit((clean_all_resource(data, MALLOC), EXIT_FAILURE));
	init_semaphores(data);
	open_semaphores(data);
	while (++i < data->num_ph)
	{
		data->philosopher[i].id = i + 1;
		data->philosopher[i].data = data;
		data->philosopher[i].num_meals = 0;
		data->philosopher[i].last_meal = 0;
	}
}

void	handling_args(data_t *data, int ac, char **av)
{
    if (ac != 5 && ac != 6)
	{
        exit((ft_putendl_fd("Error : number of argments must 5 or 6", 2), 1));
	}
	memset(data, 0, sizeof(data_t));
	data->num_ph = ft_atoi_plus(av[1]);
	data->t_die = ft_atoi_plus(av[2]);
	data->t_eat = ft_atoi_plus(av[3]);
	data->t_sleep = ft_atoi_plus(av[4]);
	data->n_times_eat = UNAVAILABLE;
	if (ac == 6)
		data->n_times_eat = ft_atoi_plus(av[5]);
	if (!data->num_ph || !data->n_times_eat)
		exit(EXIT_SUCCESS);
	data->pid = malloc(data->num_ph * sizeof(pid_t));
	if (!data->pid)
		exit((clean_all_resource(data, MALLOC), EXIT_FAILURE));
}
