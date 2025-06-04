/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 11:33:59 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

bool	open_semaphores(data_t *data)
{
	data->forks = sem_open(SEM_FORKS, O_CREAT, S_IRUSR | S_IWUSR, data->num_ph); // free
	data->simulation_stop = sem_open(SEM_STOP, O_CREAT, S_IRUSR | S_IWUSR, 1); // free
	data->kill = sem_open(SEM_KILL, O_CREAT, S_IRUSR | S_IWUSR, 0); // free
	data->write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (data->forks == SEM_FAILED || data->simulation_stop  == SEM_FAILED
		|| data->kill == SEM_FAILED)
		return(false); // free

	return(true); // free
}

void	handling_args(data_t *data, pid_t **pid, int ac, char **av)
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
	*pid = malloc(data->num_ph * sizeof(pid_t));
	if (!*pid)
		exit((ft_putendl_fd("error : init_bonus:36 malloc()", STDERR_FILENO), EXIT_FAILURE));
}

void	allocate_initial(philo_t **philosopher, data_t *data)
{
	int	i;

	i = -1;
	*philosopher = malloc(data->num_ph * sizeof(philo_t));
	if (!*philosopher)
		exit((ft_putendl_fd("error : malloc", STDERR_FILENO), EXIT_FAILURE));

	if (open_semaphores(data) == false)
		exit((ft_putendl_fd("open_semaphores() fail\n", 2), 1));

	while (++i < data->num_ph)
	{
		(*philosopher)[i].id = i + 1;
		(*philosopher)[i].data = data;
		(*philosopher)[i].num_meals = 0;
		(*philosopher)[i].last_meal = 0;
	}
}
