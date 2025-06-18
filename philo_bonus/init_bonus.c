/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 19:01:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	clean_all_resource(t_data *data, t_err err)
{
	kill_process(data);
	close_semaphores(data);
	unlink_semaphore(data);
	if (data->philosopher)
		free(data->philosopher);
	data->philosopher = NULL;
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	if (err == ARG)
		ft_putendl_fd("Error : Input", 2);
	if (err == MALLOC)
		ft_putendl_fd("Error : malloc", 2);
	if (err == FORK)
		ft_putendl_fd("Error : fork", 2);
	if (err == SEM_OPEN)
		ft_putendl_fd("Error : sem_open()", 2);
}

void	allocate_initial(t_data *data)
{
	int	i;

	i = -1;
	data->philosopher = malloc(data->num_ph * sizeof(t_philo));
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

void	handling_args(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		exit((ft_putendl_fd("Error : number of argments must 5 or 6", 2), 1));
	}
	memset(data, 0, sizeof(t_data));
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
