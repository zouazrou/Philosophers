/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/18 13:29:56 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

ms_t	ft_atoi_plus(const char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;

	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((ft_putendl_fd("Error : time must be positive (-_-)", 2), EXIT_FAILURE));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((ft_putendl_fd("Error : argument must be digit", 2), EXIT_FAILURE));
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb);
}

/*
READ F* MANUAL CHAPTER :ERRORS
*/
ms_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((ms_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

ms_t	time_simulation(data_t *data)
{
	ms_t		curr_time;

	curr_time = get_time();
	return (curr_time - data->start_time);
}

void	kill_process(data_t *data)
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

void	clean_all_resource(data_t *data, t_err err)
{
	/******kill******/
	kill_process(data);
	/******close sem******/
	close_semaphores(data);
	/******unlink sem*****/
	unlink_semaphore(data);
	// sem_close(data->forks);

	/********free*********/
	if (data->philosopher)
		free(data->philosopher);
	data->philosopher = NULL;
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	/******print msg error*****/
	if (err == ARG)
		ft_putendl_fd("Error : Input", 2);
	if (err == MALLOC)
		ft_putendl_fd("Error : malloc", 2);
	if (err == FORK)
		ft_putendl_fd("Error : fork", 2);
	if (err == SEM_OPEN)
		ft_putendl_fd("Error : sem_open()", 2);
}
