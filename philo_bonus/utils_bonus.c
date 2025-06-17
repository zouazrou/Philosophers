/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/04 22:23:43 by zouazrou         ###   ########.fr       */
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

void	unlink_semaphore(int num)
{
	int		i;
	char	*name_sem;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_KILL);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_PH_FULL);
	i = -1;
	while (++i < num)
	{
		name_sem = generate_namesem(SEM_MEAL, i);
		if (!name_sem)
			exit((ft_putendl_fd("error : generate_namesem()", 2), EXIT_FAILURE));
		sem_unlink(name_sem);
		free(name_sem);
	}
	
}
void	clean_all_resource(data_t *data, philo_t **philosopher, pid_t **pid, int num_sem)
{
	// int	i;

	// i = -1;
	unlink_semaphore(num_sem);
	free(*philosopher);
	*philosopher = NULL;
	sem_close(data->forks);
	if (pid || *pid)
		free(*pid);
}
