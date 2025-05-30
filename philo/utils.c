/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/30 23:20:07 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

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
	// while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
	// 	i++;

	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		exit((ft_putendl_fd("Error : time must be positive (-_-)", 2), 1));
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			exit((ft_putendl_fd("Error : argument must be digit", 2), 1));
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

ms_t	time_simulation(void)
{
	ms_t		curr_time;
	static ms_t	start_time;

	if (!start_time)
	{
		start_time = get_time();
		return (start_time);
	}
	curr_time = get_time();
	return (curr_time - start_time);
}

void	clean_all_resource(data_t *data, pthread_t **ids)
{
	int	i;

	// fprintf(stderr, "clean all resource\n");
	// free array of id threads
	if (*ids)
	{
		free(*ids);
		*ids = NULL;
	}
	// destroy every mutex inside data_t struct and forks
	pthread_mutex_destroy(&data->simulation_mutex);
	pthread_mutex_destroy(&data->display);
	i = -1;
	while (++i < data->num_ph)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosopher[i].meal_mutex);
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philosopher)
	{
		free(data->philosopher);
		data->philosopher = NULL;
	}
}
